@page property_definition Property Definitions

@tableofcontents



@section section1 What is a property definition?

A property definition, is a definition that tells us a property of a language. This could be the lexicon, grammar, semantics or something different.

Property definitions are very important throughout Deamer.



@section section2 What property definitions exist?

There exists several property definitions. We categorize them in 3 groups:

- main, supported by Deamer
- tool, supported by third party
- special, supported by Deamer



The following list shows all the known implemented property definitions:

- Lexicon
- Grammar



@section section3 Property Definition utilities

Each property definition has a set of default "utilities", that each definition has to implement. These utilities are used to handle properties in general.

E.g. language references uses the basic utilities to automatically look for specific objects in a language definition.



A list of all utilities:

- Type to enum convertors, for LPD and LDO
- Enum to Type convertors, for LPD and LDO
- Is LDO part of LPD validator
- Has LPD specific LDO validator
- Get all LDO's existing in LPD validator

These utilities, can be used to make generic algorithms or to more easily use LPD's and LDO's.