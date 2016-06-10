#include "bezierPatchGroup.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

BezierPatchGroup::BezierPatchGroup() {
}

void BezierPatchGroup::createSinusoidalExample() {
  int uPatches = 4;
  int vPatches = 4;

  vector<float> heightmap;
  for (int z = 0; z < 4*3+1; ++z) {
    for (int x = 0; x < 4*3+1; ++x) {
      float height = 0.0f;
      int multipler = (z/3)%2==0 ? -1 : +1;
      if (z%3==1 || z%3==2) 
        height = 2.0f;
      heightmap.push_back(multipler*height);
    }
  }

  createFromHeightmap(30.0f, 30.0f, uPatches, vPatches, heightmap);
}

void BezierPatchGroup::createWavesExample() {
  int uPatches = 4;
  int vPatches = 4;

  vector<float> heightmap;
  for (int z = 0; z < 4*3+1; ++z) {
    for (int x = 0; x < 4*3+1; ++x) {
      float height = 0.0f;

      int multipler1 = (z/3)%2==0 ? -1 : +1;
      int multipler2 = (x/3)%2==0 ? -1 : +1;

      if ((z%3==1 || z%3==2) && (x%3==1 || x%3==2)) 
        height = 2.0f;

      heightmap.push_back(multipler1*multipler2*height);
    }
  }

  createFromHeightmap(30.0f, 30.0f, uPatches, vPatches, heightmap);
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
