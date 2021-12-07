#ifndef DEAMER_TOOL_TYPE_DEAMERDEFAULTAPPLICATION_ASTVIEWER_ASTVIEWER_H
#define DEAMER_TOOL_TYPE_DEAMERDEFAULTAPPLICATION_ASTVIEWER_ASTVIEWER_H

#include "Deamer/Tool/Type/DeamerDefaultApplication/DeamerDefaultApplication.h"

namespace deamer::tool::type::deamerdefaultapplication
{
	class AstViewer
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

#endif // DEAMER_TOOL_TYPE_DEAMERDEFAULTAPPLICATION_ASTVIEWER_ASTVIEWER_H
