#include "bezierPatchGroup.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

BezierPatchGroup::BezierPatchGroup() {
}

void BezierPatchGroup::createSinusoidalExample() {
}

void BezierPatchGroup::createWavesExample() {
}

void BezierPatchGroup::createFromHeightmap(
  float width,
  float length,
  int uPatches, 
  int vPatches, 
  vector<float> heightmap
) {
  int uPoints = 3 * uPatches + 1;
  int vPoints = 3 * vPatches + 1;
  assert(uPoints * vPoints == heightmap.size());
  float patchWidth = width / uPatches;
  float patchLength = length / vPatches;

  _patches.clear();
  for (int pz = 0; pz < vPatches; ++pz) {
    for (int px = 0; px < uPatches; ++px) {
      vector<float> patchHeightmap;

      int z0 = 3 * pz;
      int x0 = 3 * px;
      for (int z = 0; z < 4; ++z) {
        for (int x = 0; x < 4; ++x) {
          patchHeightmap.push_back(heightmap[(z0+z)*vPoints + x0 + x]);
        }
      }

      BezierPatch patch;
      patch.createFromHeightmap(patchWidth, patchLength, patchHeightmap);
      _patches.push_back(patch);
    }
  }

  _uPatches = uPatches;
  _vPatches = vPatches;
  _width = width;
  _length = length;
}

void BezierPatchGroup::drawPatches(EffectBase *effect) const {
  float patchWidth = _width / _uPatches;
  float patchLength = _length / _vPatches;
  float Rx = (_uPatches - 1) * patchWidth;
  float Rz = (_vPatches - 1) * patchLength;

  for (int z = 0; z < _vPatches; ++z) {
    for (int x = 0; x < _uPatches; ++x) {
      auto index = z * _vPatches + x;
      float dz = (z/((float)_vPatches-1)) * Rz - 0.5f * Rz;
      float dx = (x/((float)_uPatches-1)) * Rx - 0.5f * Rx;
      auto model = glm::translate(glm::mat4(1.0f), glm::vec3(dx, 0.0f, dz));
      effect->setModelMatrix(model);
      _patches[index].drawPatch();
    }
  }
}

void BezierPatchGroup::drawControlNets(EffectBase *effect) const {
  float patchWidth = _width / _uPatches;
  float patchLength = _length / _vPatches;
  float Rx = (_uPatches - 1) * patchWidth;
  float Rz = (_vPatches - 1) * patchLength;

  for (int z = 0; z < _vPatches; ++z) {
    for (int x = 0; x < _uPatches; ++x) {
      auto index = z * _vPatches + x;
      float dz = (z/((float)_vPatches-1)) * Rz - 0.5f * Rz;
      float dx = (x/((float)_uPatches-1)) * Rx - 0.5f * Rx;
      auto model = glm::translate(glm::mat4(1.0f), glm::vec3(dx, 0.0f, dz));
      effect->setModelMatrix(model);
      _patches[index].drawControlNet();
    }
  }
}
