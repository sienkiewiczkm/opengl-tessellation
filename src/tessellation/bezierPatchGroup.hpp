#ifndef __BEZIER_PATCH_GROUP_HPP__
#define __BEZIER_PATCH_GROUP_HPP__

#include "bezierPatch.hpp"
#include "effectBase.hpp"

#include <vector>

class BezierPatchGroup {
public:
  BezierPatchGroup();

  void createSinusoidalExample();
  void createWavesExample();
  void createFromHeightmap(float width, float length, 
      int uPatches, int vPatches, std::vector<float> heightmap);

  void drawPatches(BezierPatchEffect *effect) const;
  void drawControlNets(EffectBase *effect) const;

private:
  float _width, _length;
  int _uPatches, _vPatches;
  std::vector<BezierPatch> _patches;
};

#endif
