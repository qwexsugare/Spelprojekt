//Made by Emil Rudvi
//------------------

#pragma once

#include "stdafx.h"
#include <stdio.h>
#include <ctype.h>

class MyText
{
private:
	struct writeText
	{
		D3DXVECTOR3 POS;
		/*D3DXCOLOR COLOR;*/
		D3DXVECTOR2 UV;
		D3DXVECTOR3 NORMAL;
	};

	ID3D10Buffer* m_VertexBuffer;
	ID3D10ShaderResourceView *m_texture;
	vector<writeText> m_textS;
	int m_numberOfPoints;
	D3DXCOLOR m_color;
	D3DXVECTOR3 m_pos;
	string m_str;
	float m_size;
	float m_height;
	float m_width;
	float m_FontSize;
public:
	MyText();
	MyText(ID3D10Device* _device, ID3D10ShaderResourceView* _texture, float _height, float _width, D3DXCOLOR _color, D3DXVECTOR3 _pos, float _size);
	~MyText();
	
	ID3D10Buffer* getBuffer()const { return this->m_VertexBuffer; }
	ID3D10ShaderResourceView* getTexture()const { return this->m_texture; }
	int getNumberOfPoints()const { return this->m_numberOfPoints; }
	D3DXMATRIX getModelMatrix();

	//----------------------------------------------------------------------------------------------------------------------------
	//	Changes text position
	//----------------------------------------------------------------------------------------------------------------------------
		void setPos(D3DXVECTOR3 _pos);
	//----------------------------------------------------------------------------------------------------------------------------
	//	Used to type the text on to the screen
	//----------------------------------------------------------------------------------------------------------------------------
		DECLDIR void DrawString(string str, float _size = -2);
	//----------------------------------------------------------------------------------------------------------------------------
	//	Convert float to string
	//----------------------------------------------------------------------------------------------------------------------------
		string SendString(float floatInput);
		string SendStringINT(int intInput);
	//----------------------------------------------------------------------------------------------------------------------------
	//	Functions for buffer
	//----------------------------------------------------------------------------------------------------------------------------
		UINT GetStride();
		int GetVertexNumber();
	//----------------------------------------------------------------------------------------------------------------------------
		
		void Render()const;
};