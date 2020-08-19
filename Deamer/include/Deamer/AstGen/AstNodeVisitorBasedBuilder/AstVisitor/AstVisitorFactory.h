/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTVISITOR_ASTVISITORFACTORY_H
#define DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTVISITOR_ASTVISITORFACTORY_H
#include <memory>

namespace deamer {
	namespace AstVisitorBuilder {

		class AstVisitorFactory
		{
		private:
		protected:
		public:
			AstVisitorFactory() = default;
			~AstVisitorFactory() = default;
		};
	}
}

#endif //DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTVISITOR_ASTVISITORFACTORY_H