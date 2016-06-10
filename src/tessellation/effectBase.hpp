#ifndef __EFFECT_BASE_HPP__
#define __EFFECT_BASE_HPP__

#include <glm/mat4x4.hpp>

class EffectBase {
public:
  virtual void setModelMatrix(const glm::mat4 &model) = 0;
};

#endif
