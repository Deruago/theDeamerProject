# Deamer, Compiler Generator

## Overview

Deamer is a compiler generator, that generates the front-end and mid-end of a compiler. Some parts can be found in the following list:

- Lexer
- Parser
- Semantic analysis
- Error handling/detection
- Integration with different compilers, and different compiler generators.
- Integration with Deamer-Lang.
- Support for Custom Tools/Custom libraries.

The thing what makes Deamer different from other compiler generators, is that not only generates a simple compiler it does thousand of things more than that. It can generate a lot of tools around your language. The compiler generator has a unique infrastructure built for making custom tools for any language.

An nice example of such tool is the default LanguageBuilder library. This library can be used in a variety of languages to generate valid compilable code, by your new language. It can also be used to compile your language in many other languages.

## Information

### Custom Tools

Custom tools are a way to add features to the generation of languages. Do you want to integrate a language A with any other generated language, or want to add some new libraries. Then Custom Tools are perfect for you. Custom Tools allow you do all the above and more. In order to learn how to create your custom tool, go to the dedicated folder for more information.

### Contributing

You can contribute in many ways:

- Create custom tools
- Fix bugs
- Review code
- Add features

All of these things is further explained in the dedicated file (CONTRIBUTING.md).