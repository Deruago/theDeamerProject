#ifndef DEAMER_TOOL_TYPE_DEAMERDEFAULTAPPLICATION_TOKENVIEWER_TOKENVIEWER_H
#define DEAMER_TOOL_TYPE_DEAMERDEFAULTAPPLICATION_TOKENVIEWER_TOKENVIEWER_H

#include "Deamer/Tool/Type/DeamerDefaultApplication/DeamerDefaultApplication.h"

namespace deamer::tool::type::deamerdefaultapplication
{
	class TokenViewer
	{
		using reference = DeamerDefaultApplication::reference;

	private:
		reference Reference;

	public:
		AstViewer(reference reference_);

	public:
		void Generate(::deamer::file::tool::Directory& output);
	};
}

#endif // DEAMER_TOOL_TYPE_DEAMERDEFAULTAPPLICATION_TOKENVIEWER_TOKENVIEWER_H
