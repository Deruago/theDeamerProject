# DST example

DST is a language used to parse (DST-) StringTemplates with.

StringTemplates are files that contain variables, which we can easily insert using DST.

DST is thus very nice for code generation.

## Example overview

For DST we use Deamer 2.0.0 (pre-release). We will use Deamer C++ and won't touch DLDL in this example.

The example is split up in the following sections:

- Defining your language
- Compiling your project
- Using the output



## Defining our language

This part will go over the varies definitions you can define:

- Lexicon
- Grammar
- Identity
- Generation

### Types of definitions

You have 2 main definitions:

- Required definitions, these definitions need to be always defined.
- Non-required definitions, these definitions are optional.

#### Required definitions

- Identity, used to specify information about the language. E.g. its name.
- Generation, used to specify which tools need to be generated and how.

#### Non-required definitions



- Lexicon
- Grammar

These definitions are optional, but if you want to create a language you of course need to define these two.

### Defining an definition

#### Identity

#### Lexicon

#### Grammar

#### Generation

