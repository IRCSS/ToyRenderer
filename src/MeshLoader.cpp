#include "MeshLoader.h"
#include "ResourceManager.h"
#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#endif 

#include "vendor/meshReader/tinyobjloader.h"
#include <fstream>
#include <string>

class Color;
class Texture;

namespace ToyRenderer {

	bool texture_exists(std::string filename) {
		std::ifstream ifile(filename);
		return !ifile.fail();
	}


	bool TryAddTexture(Material* m, const char* basepath, const std::string& textureName, const std::string& targetMaterialAttName) {
		if(textureName.empty()) return false;
		if (!texture_exists(basepath + textureName)) return false;

		Texture* bumpMap = new Texture(basepath + textureName);
		ResourceManager::resourceManagerSingelton->RegisterTexture(bumpMap);

		m->SetTexture(targetMaterialAttName, bumpMap);

		return true;

	}

	Material* ParseTinyObjMaterial(const tinyobj::material_t& m, const char* basepath) {

		Material* toReturn = new Material();
		ResourceManager::resourceManagerSingelton->RegisterMaterial(toReturn);

		toReturn->SetColor("ambientColor",  Color(m.ambient[0],  m.ambient[1],  m.ambient[2]));
		toReturn->SetColor("diffuseColor",  Color(m.diffuse[0],  m.diffuse[1],  m.diffuse[2]));
		toReturn->SetColor("specularColor", Color(m.specular[0], m.specular[1], m.specular[2]));
		toReturn->SetColor("emissionColor", Color(m.emission[0], m.emission[1], m.emission[2]));

		toReturn->SetFloat("roughnessValue", m.roughness);
		toReturn->SetFloat("metalicValue",   m.metallic);


		TryAddTexture(toReturn, basepath, m.diffuse_texname,      "diffuseMap");
		TryAddTexture(toReturn, basepath, m.ambient_texname,      "ambientMap");
		TryAddTexture(toReturn, basepath, m.bump_texname,         "bumpMap");
		TryAddTexture(toReturn, basepath, m.normal_texname,       "normalMap");
		TryAddTexture(toReturn, basepath, m.displacement_texname, "displacmentMap");
		TryAddTexture(toReturn, basepath, m.emissive_texname,     "emmisveMap");
		TryAddTexture(toReturn, basepath, m.metallic_texname,     "metalicMap");
		TryAddTexture(toReturn, basepath, m.roughness_texname,    "roughnessMap");
		TryAddTexture(toReturn, basepath, m.specular_texname,     "specularMap");
		return toReturn;
	}

	RawMesh* MeshLoader::LoadTinyObj(const char* filename, const char* basepath, bool triangulate)
	{

		// ------------------------------------------------------------------------------------------------------
		tinyobj::attrib_t                attrib;
		std::vector<tinyobj::shape_t>    shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, basepath, filename, triangulate);
		// ------------------------------------------------------------------------------------------------------

		if (!warn.empty()) {
			std::cout << "WARN: " << warn << std::endl;
		}



		if (!err.empty()) {
			std::cerr << "ERR: " << err << std::endl;
		}



		if (!ret) {
			std::cout << "Failed to load/parse .obj.\n" << std::endl;
			return false;
		}

		// ------------------------------------------------------------------------------------------------------
		// load materials in rawMesh as Material
		RawMesh* m = new RawMesh();
		for (int i = 0; i < materials.size(); i++) {
			m->m_materials.push_back(ParseTinyObjMaterial(materials[i], basepath));
		}
	


		m->m_subShapesCount = shapes.size();
		for (size_t s = 0; s < shapes.size(); s++) {
			
			m->m_subShapes.push_back(t_RawMeshSubShape(shapes[s].mesh.num_face_vertices.size()));
			
			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f];

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {

					

					// access to vertex
					tinyobj::index_t idx  = shapes[s].mesh.indices[index_offset + v];
					m->m_subShapes[s].m_facesIndices.push_back(t_RawMeshIndices(idx.vertex_index, idx.normal_index, idx.texcoord_index));


					tinyobj::real_t  vx   = attrib.vertices[3 * idx.vertex_index + 0];
					tinyobj::real_t  vy   = attrib.vertices[3 * idx.vertex_index + 1];
					tinyobj::real_t  vz   = attrib.vertices[3 * idx.vertex_index + 2];
					tinyobj::real_t  nx   = attrib.normals[3 * idx.normal_index + 0];
					tinyobj::real_t  ny   = attrib.normals[3 * idx.normal_index + 1];
					tinyobj::real_t  nz   = attrib.normals[3 * idx.normal_index + 2];
					tinyobj::real_t  tx   = attrib.texcoords[2 * idx.texcoord_index + 0];
					tinyobj::real_t  ty   = attrib.texcoords[2 * idx.texcoord_index + 1];
					// Optional: vertex colors
					// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
					// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
					// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
				}
				index_offset += fv;

				// per-face material
				shapes[s].mesh.material_ids[f];

			}


		}




		return m;
	}

}