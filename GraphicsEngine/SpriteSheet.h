#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include "stdafx.h"
#include "VertexStructs.h"
#include "DataStructures.h"
#include "DeviceHandler.h"
#include "SpriteEffectFile.h"

class SpriteSheet
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
public:
	SpriteSheet(DeviceHandler *deviceHandler, ID3D10ShaderResourceView* _texture, INT2 _position, INT2 _size, INT2 _nrOfFrames);

	ID3D10Buffer *getBuffer();
	ID3D10ShaderResourceView *getTexture();
	D3DXMATRIX getModelMatrix();
	int getStartIndex();
	int getNrOfVertices();

	void setPosition(INT2 _position);
	void setSize(INT2 _size);

	void setCurrentFrame(INT2 _currentFrame);
	void playAnimation(INT2 _startFrame, INT2 _endFrame, bool _loop, int _framesPerSecond);
	void stopAnimation();

	void update(float dt);
};

#endif