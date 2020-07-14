#define GET_MACRO_NAMESPACE(_1,_2,NAME,...) NAME
#define GET_MACRO_VAR(_1,_2,_3,NAME,...) NAME

#define new_namespace(...) GET_MACRO_NAMESPACE(__VA_ARGS__, new_namespace2, new_namespace1) (__VA_ARGS__)
#define new_var(...) GET_MACRO_VAR(__VA_ARGS__, new_var2, new_var1) (__VA_ARGS__)

#define new_namespace1(name) FileNamespaceSection* name = new FileNamespaceSection(#name);
#define new_namespace2(base_namespace, name) FileNamespaceSection* name = new FileNamespaceSection(base_namespace, #name);
#define new_class(name, scope) FileClassSection* name = new FileClassSection(#name, scope);
#define new_var1(class, name) FileVariable* name = new FileVariable(class, #name, false);
#define new_var2(class, name, is_member) FileVariable* name = new FileVariable(class, #name, is_member);
#define get_output(langtype) std::cout << langtype->GetOutput();