#pragma once
#include "effectfile.h"

class ParticleEngineEffectFile : public EffectFile
{
private:
	ID3D10EffectShaderResourceVariable* m_texture;
	ID3D10EffectShaderResourceVariable* m_randomTexture;
	ID3D10InputLayout* m_vertexLayout;

	ID3D10EffectTechnique* m_beaconSOTechnique;
	ID3D10EffectTechnique* m_drawBeaconTechnique;
	ID3D10EffectTechnique* m_upSideDownTwistSOTechnique;
	ID3D10EffectTechnique* m_drawUpSideDownTwistTechnique;
	ID3D10EffectTechnique* m_circlePulsSOTechnique;
	ID3D10EffectTechnique* m_drawCirclePulsTechnique;
	ID3D10EffectTechnique* m_sphereSOTechnique;
	ID3D10EffectTechnique* m_drawSphereTechnique;
	

	ID3D10EffectVectorVariable* camPosW;
	ID3D10EffectVectorVariable* emitPosW;
	ID3D10EffectVectorVariable* emitDirW;
	ID3D10EffectVectorVariable* size;
	ID3D10EffectScalarVariable* totalTime;
	ID3D10EffectScalarVariable* dt;
	ID3D10EffectMatrixVariable* viewProj;
	ID3D10EffectScalarVariable* isAlive;
public:
	ParticleEngineEffectFile();
	ParticleEngineEffectFile(ID3D10Device* _device);
	~ParticleEngineEffectFile();
	
	ID3D10EffectTechnique* getBeaconSOTechnique();
	ID3D10EffectTechnique* getDrawBeaconTechnique();
	ID3D10EffectTechnique* getUpSideDownTwistSOTechnique();
	ID3D10EffectTechnique* getDrawUpSideDownTwistTechnique();
	ID3D10EffectTechnique* getCirclePulsSOTechnique();
	ID3D10EffectTechnique* getDrawCirclePulsTechnique();
	ID3D10EffectTechnique* getSphereSOTechnique();
	ID3D10EffectTechnique* getDrawSphereTechnique();


	ID3D10InputLayout* getInputLayout() {return this->m_vertexLayout;}

	void setTexture(ID3D10ShaderResourceView* _texture);
	void setRandomTexture(ID3D10ShaderResourceView* _texture);
	void setCameraPos(D3DXVECTOR4 _cameraPos);
	void setEmitPos(D3DXVECTOR4 _emitPos);
	void setEmitDir(D3DXVECTOR4 _emitDir);
	void setTotalTime(float _time);
	void setDt(float _dt);
	void setSize(D3DXVECTOR2 _size);
	void setViewProj(D3DXMATRIX _matrix);
	void setIsAlive(bool _alive);
};