#include "MeshLoader.h"
#include "managers/ResourceManager.h"
#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#endif 

#include "vendor/meshReader/tinyobjloader.h"
#include <fstream>
#include <string>
#include "log/log.h"

class Texture;

namespace ToyRenderer {
	class Color;

	bool texture_exists(const std::string& basePass, const std::string& filename) {

		std::string fullPath = basePass + "/" + filename;
		std::ifstream ifile(fullPath);
		return !ifile.fail();
	}


	bool TryAddTexture(Material* m, const char* basepath, const std::string& textureName, const std::string& targetMaterialAttName) {
		if(textureName.empty()) return false;
		if (!texture_exists(basepath, textureName)) return false;


		std::string fullPath = std::string(basepath) + "/" + textureName;
		Texture* t = new Texture(fullPath);
		ResourceManager::Instance().RegisterTexture(t);

		m->SetTexture(targetMaterialAttName, t);

		return true;

	}

	Material* ParseTinyObjMaterial(const tinyobj::material_t& m, const char* basepath) {

		Material* toReturn = new Material();
		ResourceManager::Instance().RegisterMaterial(toReturn);

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


	/// Load Raw Mesh using Tiny OBJ.
	/// \pram filename is the compelete path to the file, for example D:/.../file.obj
	/// \pram basepath is like above but without the file.obj
	RawMesh* MeshLoader::LoadTinyObj(const char* filename, const char* basepath)
	{
		bool triangulate = true; // For now to keep things simple I will only support triangulated meshes.

		// ------------------------------------------------------------------------------------------------------
		tinyobj::attrib_t                attrib;
		std::vector<tinyobj::shape_t>    shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		std::string s_fileName(filename);
		std::replace(s_fileName.begin(), s_fileName.end(), '\\', '/');

		std::string s_basepath(basepath);
		std::replace(s_basepath.begin(), s_basepath.end(), '\\', '/');

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, s_fileName.c_str(), s_basepath.c_str(),  triangulate);
		// ------------------------------------------------------------------------------------------------------

		if (!warn.empty()) ENGINE_LOG_WARN(" During loading of {}, WARN: {}" , s_fileName, warn );

		if (!err.empty())  ENGINE_LOG_ERROR(" During loading of {}, ERROR: {}", s_fileName, err);
		
		if (!ret) {
			ENGINE_LOG_ERROR(" Failed to load/parse.obj. {}: {}", s_fileName);
			return false;
		}

		// ------------------------------------------------------------------------------------------------------
		// load materials in rawMesh as Material
		RawMesh* m = new RawMesh();
		for (int i = 0; i < materials.size(); i++) {
			m->m_materials.push_back(ParseTinyObjMaterial(materials[i], s_basepath.c_str()));
		}
	
		

		m->m_subShapesCount = (int) shapes.size();
		for (size_t s = 0; s < shapes.size(); s++) {
			
			m->m_subShapes.push_back(t_RawMeshSubShape((int)shapes[s].mesh.num_face_vertices.size()));
			
			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f];

				m->m_subShapes[s].m_FaceMaterialIndex.push_back(shapes[s].mesh.material_ids[f]);

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {

					

					// access to vertex
					tinyobj::index_t idx  = shapes[s].mesh.indices[index_offset + v];
					
					
					// To DO: once you start implementing a proper index buffer, you can use an architecture like below
					//m->m_subShapes[s].m_facesIndices.push_back(t_RawMeshIndices(idx.vertex_index, idx.normal_index, idx.texcoord_index, idx.vertex_index));
					m->m_subShapes[s].m_facesIndices.push_back(t_RawMeshIndices((int)m->m_VertexPositions.size(), (int)m->m_VertexNormals.size(), (int)m->m_uv.size(), (int)m->m_VertexPositions.size())); // Explicit cast to 16 bit int is an issue for meshes with more than 65k vertices. 
					if (3 * idx.vertex_index  < attrib.vertices.size()) {
						tinyobj::real_t  vx = attrib.vertices[3 * idx.vertex_index + 0];
						tinyobj::real_t  vy = attrib.vertices[3 * idx.vertex_index + 1];
						tinyobj::real_t  vz = attrib.vertices[3 * idx.vertex_index + 2];
						Vector3 vertexPosition(vx, vy, vz);
						m->m_VertexPositions.push_back(vertexPosition);
					}

					if (3 * idx.normal_index  < attrib.normals.size() ) {
					tinyobj::real_t  nx   = attrib.normals[3 * idx.normal_index + 0];
					tinyobj::real_t  ny   = attrib.normals[3 * idx.normal_index + 1];
					tinyobj::real_t  nz   = attrib.normals[3 * idx.normal_index + 2];
					Vector3 vertexNormal(nx, ny, nz);
					m->m_VertexNormals.push_back(vertexNormal);

					}


					if (2 * idx.texcoord_index < attrib.texcoords.size()) {
						tinyobj::real_t  tx = attrib.texcoords[2 * idx.texcoord_index + 0];
						tinyobj::real_t  ty = attrib.texcoords[2 * idx.texcoord_index + 1];
						Vector2 vertexTexcoord1(tx, ty);
						m->m_uv.push_back(vertexTexcoord1);
					}

					if (3 * idx.vertex_index < attrib.colors.size()) {
						tinyobj::real_t red = attrib.colors[3 * idx.vertex_index + 0];
						tinyobj::real_t green = attrib.colors[3 * idx.vertex_index + 1];
						tinyobj::real_t blue = attrib.colors[3 * idx.vertex_index + 2];

						Color vertexColor(red, green, blue);

						m->m_VertexColors.push_back(vertexColor);
					}
				}
				index_offset += fv;

			}


		}




		return m;
	}

}