#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(DeviceHandler *deviceHandler, ID3D10ShaderResourceView* _texture, FLOAT2 _position, FLOAT2 _size, INT2 _nrOfFrames, int _layer)
{
	this->m_texture = _texture;
	this->m_nrOfFrames = _nrOfFrames;
	this->m_layer = _layer;

	this->m_currentFrame = 0;
	this->m_startFrame = 0;
	this->m_endFrame = 0;
	this->m_timePerFrame = 0.0f;
	this->m_animationTimer = 0.0f;

	//Convert the position and size from pixels to projection space
	//this->m_position.x = ((float)_position.x / deviceHandler->getScreenSize().x) * 2 - 1;
	//this->m_position.y = ((float)_position.y / deviceHandler->getScreenSize().y) * 2 - 1;

	//this->m_size.x = ((float)_size.x / deviceHandler->getScreenSize().x) * 2;
	//this->m_size.y = ((float)_size.y / deviceHandler->getScreenSize().y) * 2;

	this->m_position = FLOAT2((float)_position.x, (float)_position.y);
	this->m_size = FLOAT2((float)_size.x, (float)_size.y);

	//Create modelmatrix
	D3DXMatrixTranslation(&this->m_modelMatrix, this->m_position.x, this->m_position.y, 0.0f);

	//Create the buffer
	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * this->m_nrOfFrames.x * this->m_nrOfFrames.y * 6;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT hr = deviceHandler->getDevice()->CreateBuffer( &bd, 0, &this->m_buffer);

	if(FAILED(hr))
	{
		MessageBox( 0, "Unable to create Vertex Buffer", "VB Error", 0 );
	}

	//Load vertices
	Vertex *vertexData = NULL;
	FLOAT2 pos = FLOAT2(-this->m_size.x / 2, -this->m_size.y / 2);

	this->m_buffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));

	int i = 0;

	for(int y = 0; y < this->m_nrOfFrames.y; y++)
	{
		for(int x = 0; x < this->m_nrOfFrames.x; x++)
		{
			vertexData[i].pos = D3DXVECTOR3(pos.x, pos.y + this->m_size.y, 0.0f);
			vertexData[i].texCoord = D3DXVECTOR2((float)x / this->m_nrOfFrames.x, (float)(y) / this->m_nrOfFrames.y);
			i++;

			vertexData[i].pos = D3DXVECTOR3(pos.x + this->m_size.x, pos.y, 0.0f);
			vertexData[i].texCoord = D3DXVECTOR2((float)(x + 1.0f) / this->m_nrOfFrames.x, (float)(y + 1.0f) / this->m_nrOfFrames.y);
			i++;

			vertexData[i].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
			vertexData[i].texCoord = D3DXVECTOR2((float)x / this->m_nrOfFrames.x, (float)(y + 1.0f) / this->m_nrOfFrames.y);
			i++;

			vertexData[i].pos = D3DXVECTOR3(pos.x + this->m_size.x, pos.y, 0.0f);
			vertexData[i].texCoord = D3DXVECTOR2((float)(x + 1.0f) / this->m_nrOfFrames.x, (float)(y + 1.0f) / this->m_nrOfFrames.y);
			i++;

			vertexData[i].pos = D3DXVECTOR3(pos.x + this->m_size.x, pos.y + this->m_size.y, 0.0f);
			vertexData[i].texCoord = D3DXVECTOR2((float)(x + 1.0f) / this->m_nrOfFrames.x, (float)(y) / this->m_nrOfFrames.y);
			i++;

			vertexData[i].pos = D3DXVECTOR3(pos.x, pos.y + this->m_size.y, 0.0f);
			vertexData[i].texCoord = D3DXVECTOR2((float)x / this->m_nrOfFrames.x, (float)(y) / this->m_nrOfFrames.y);
			i++;
		}
	}

	this->m_buffer->Unmap();
}

ID3D10Buffer *SpriteSheet::getBuffer()
{
	return this->m_buffer;
}

ID3D10ShaderResourceView *SpriteSheet::getTexture()
{
	return this->m_texture;
}

D3DXMATRIX SpriteSheet::getModelMatrix()
{
	return this->m_modelMatrix;
}

int SpriteSheet::getStartIndex()
{
	return this->m_currentFrame * 6;
}

int SpriteSheet::getNrOfVertices()
{
	return 6;
}

int SpriteSheet::getLayer()
{
	return this->m_layer;
}

void SpriteSheet::setPosition(INT2 _position)
{
	D3DXMatrixTranslation(&this->m_modelMatrix, this->m_position.x, this->m_position.y, 0.0f);
}

void SpriteSheet::setSize(INT2 _size)
{
	//Scaling?
}

void SpriteSheet::setCurrentFrame(INT2 _currentFrame)
{
	this->m_currentFrame = _currentFrame.y * this->m_nrOfFrames.x + _currentFrame.x;
}

INT2 SpriteSheet::getCurrentFrame()
{
	return INT2(this->m_currentFrame / this->m_nrOfFrames.x, this->m_currentFrame - this->m_currentFrame / this->m_nrOfFrames.x);
}

void SpriteSheet::playAnimation(INT2 _startFrame, INT2 _endFrame, bool _loop, int _framesPerSecond)
{
	this->m_startFrame = _startFrame.y * this->m_nrOfFrames.x + _startFrame.x;
	this->m_endFrame = _endFrame.y * this->m_nrOfFrames.x + _endFrame.x;
	this->m_timePerFrame = 1.0f / _framesPerSecond;
	this->m_loop = _loop;
	this->m_animationTimer = 0.0f;

	this->m_currentFrame = this->m_startFrame;
}

void SpriteSheet::stopAnimation()
{
	this->m_timePerFrame = 0;
}

void SpriteSheet::update(float dt)
{
	if(this->m_timePerFrame > 0.0f)
	{
		this->m_animationTimer = this->m_animationTimer + dt;

		if(this->m_animationTimer > this->m_timePerFrame)
		{
			int framesToMoveForward = this->m_animationTimer / this->m_timePerFrame;
			this->m_animationTimer  = this->m_animationTimer - framesToMoveForward * this->m_timePerFrame;

			this->m_currentFrame = this->m_currentFrame + framesToMoveForward;

			if(this->m_currentFrame > this->m_endFrame)
			{
				if(this->m_loop == true)
				{
					this->m_currentFrame = this->m_startFrame;
				}
				else
				{
					this->m_currentFrame = this->m_endFrame;
					this->m_timePerFrame = 0.0f;
				}
			}
		}
	}
}