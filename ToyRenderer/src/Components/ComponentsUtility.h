#pragma once
#include "log/Log.h"
#include "system/DebugBreak.h"
#include "world/GameObject.h"

// Example REQUIRE_COMPONENT(Transform, "Transform", "AudioListner"); This will assert if at the momment of calling this macro, the component can access a transform attached to the gameobject
#define REQUIRE_COMPONENT(componentType, componentName, callerIdentifier) if(this->gameObject == nullptr) {                                                                                                                                   \
                                                                          ENGINE_LOG_ERROR("Component {} Requires Component {}, however no gameobject is attached to it", callerIdentifier, componentName);                                   \
                                                                          DEBUG_BREAK; }                                                                                                                                                      \
                                                                          if(gameObject->GetComponent<componentType>() == nullptr) {                                                                                                          \
                                                                          ENGINE_LOG_ERROR("Component {} Requires Component {}, however no such component is attachted to gameobject {}", callerIdentifier, componentName, gameObject->name); \
                                                                          DEBUG_BREAK;}                                                                                                                                                       \
 