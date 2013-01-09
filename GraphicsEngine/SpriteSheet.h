#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include "stdafx.h"
#include "SpriteBase.h"
#include "VertexStructs.h"
#include "DataStructures.h"
#include "DeviceHandler.h"
#include "SpriteEffectFile.h"

class SpriteSheet : public SpriteBase
{
private:
	ID3D10Buffer* m_buffer;
	ID3D10ShaderResourceView* m_texture;
	D3DXMATRIX m_modelMatrix;

	INT2 m_nrOfFrames;
	int m_currentFrame;
	int m_startFrame;
	int m_endFrame;
	float m_timePerFrame;
	float m_animationTimer;
	bool m_loop;

	FLOAT2 m_size;
	FLOAT2 m_position;
	int m_layer;
public:
	SpriteSheet(DeviceHandler *deviceHandler, ID3D10ShaderResourceView* _texture, FLOAT2 _position, FLOAT2 _size, INT2 _nrOfFrames, int _layer);

	ID3D10Buffer *getBuffer();
	ID3D10ShaderResourceView *getTexture();
	D3DXMATRIX getModelMatrix();
	int getStartIndex();
	int getNrOfVertices();
	int getLayer();

	DECLDIR void setPosition(FLOAT2 _position);
	DECLDIR void setSize(FLOAT2 _size);

	DECLDIR void setCurrentFrame(INT2 _currentFrame);
	DECLDIR INT2 getCurrentFrame();
	DECLDIR void playAnimation(INT2 _startFrame, INT2 _endFrame, bool _loop, int _framesPerSecond);
	DECLDIR void stopAnimation();

	void update(float dt);
};

#endif