#pragma once
#include <vector>
#include "Glad/glad.h"
#include "Renderer.h"

struct VerteBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) 
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VerteBufferElement> m_Elements;
	unsigned int m_Stride;
	unsigned int m_RendererID;
public:
	VertexBufferLayout() :m_Stride(0) {};
	~VertexBufferLayout() {};

	template<typename T>
	void Push(unsigned int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });
		m_Stride += VerteBufferElement::GetSizeOfType(GL_FLOAT)*count;
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
		m_Stride += VerteBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;


	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
		m_Stride += VerteBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VerteBufferElement> GetElements() const { return m_Elements; };
	inline unsigned int GetStride() const { return m_Stride; }
};

