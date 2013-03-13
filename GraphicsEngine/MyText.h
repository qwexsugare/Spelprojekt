//Made by Emil Rudvi
//------------------

#pragma once

#include "stdafx.h"
#include <stdio.h>
#include <ctype.h>
#include "MyTextOffsets.h"

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
	D3DXVECTOR3 m_pos;
	string m_str;
	float m_size;
	float m_height;
	float m_width;
	float m_FontSize;
	MyTextOffsets m_myTextOffsets;
	bool m_visible;
	bool m_centered;
public:
	MyText();
	MyText(ID3D10Device* _device, ID3D10ShaderResourceView* _texture, string _offsetPath, string _offsetFilename, float _height, float _width, D3DXVECTOR3 _pos, float _size, bool _centered = false);
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
		DECLDIR void setVisible(bool _visible);
	//----------------------------------------------------------------------------------------------------------------------------
	//	Convert float to string
	//----------------------------------------------------------------------------------------------------------------------------
		static string FloatToString(float floatInput);
		static string IntToString(int intInput);
	//----------------------------------------------------------------------------------------------------------------------------
	//	Functions for buffer
	//----------------------------------------------------------------------------------------------------------------------------
		UINT GetStride();
		int GetVertexNumber();
		bool getVisible();
};