#pragma once

namespace Nugget
{
	class ShaderImplement
	{
	public:
		virtual void Bind() = 0;

		virtual ~ShaderImplement() {};
	};
}
