OK: [SWS_BSW_00101] Module abbreviation ⌈The Module abbreviation <Ma> of a BSW Module shall be the same as defined in the List of Basic Software Modules [1].⌋  
NA: [SWS_BSW_00102] Module implementation prefix
⌈The Module implementation prefix <Mip> shall be formed in the following way: <Ma>[_<vi>_<ai>] Where <Ma> is the Module abbreviation of the BSW Module (SWS_BSW_00101), <vi> is its vendorId and <ai> is its vendorApiInfix. The sub part in square brackets [_<vi>_<ai>] is omitted if no vendorApiInfix is defined for the BSW Module. For Complex Drivers and transformers, the <Mip> is directly derived from the apiServicePrefix.⌋
The elements vendorId and vendorApiInfix are defined in BSW Module Description Template [4]. Their usage may be obligatory in some situations, like in case of multiple instantiation of BSW Driver modules

File type, for all BSW Modules Classification Example: Com
Module documentation mandatory Not defined.
BSW Module description mandatory Not defined. See [4].
Implementation source mandatory Com.c
Implementation header mandatory Com.h
Link time configuration source conditional Com_Lcfg.c
Post-build time configuration source conditional Com_PBcfg.c
Interrupt frame implementation source conditional Gpt_Irq.c

OK: [SWS_BSW_00103] General file naming convention ⌈The name of all BSW Module implementation files shall be formed in the following way:
<Mip>[_<Ie>]*.*
The sup-part in square brackets [<Ie>] is an optional implementation specific file name extension. The wildcards * are replaced according to the different types of files specified for the module.⌋  

OK: [SWS_BSW_00170] File names are case sensitive ⌈File names shall be considered case sensitive regardless of the file system in which they are used.⌋
OK: [SWS_BSW_00171] File names are non-ambiguous
⌈It shall not be allowed to name any two files so that they only differ by the case of
their letters.⌋

OK: [SWS_BSW_00104] Restrict imported information ⌈The BSW Module shall import only the necessary information (i.e. header files) that is required to fulfill its functional requirements.⌋
OK: [SWS_BSW_00105] Restrict exported information ⌈The BSW Module shall export only that kind of information in their corresponding header files that is explicitly needed by other modules.⌋
OK: [SWS_BSW_00001] Provide BSW Module description ⌈The BSW Module description (.arxml) shall be provided for the module according to the AUTOSAR Specification of BSW Module Description Template

NG: [SWS_BSW_00002] Provide BSW Module documentation ⌈The BSW Module documentation shall be provided with the BSW Module implementation.
NG: [SWS_BSW_00003] Provide information on supported microcontroller and used tool chain
NG: [SWS_BSW_00054] Document calling sequence of Scheduled functions
NG: [SWS_BSW_00061] Document configuration rules and constraints
OK: [SWS_BSW_00004] Provide Implementation source files Mip>[_<Ie>].c
OK: [SWS_BSW_00060] Declarations within Implementation source files are restricted
⌈The Implementation source files of the BSW Module shall declare all constants,
global data types and functions that are only used by the module internally. Pre-link
time configuration parameters are an exception of this rule.⌋
To allow the compiler to check for consistency between declaration and definition of
global variables and functions, the Implementation source shall include its own
header file.

OK: [SWS_BSW_00005] Include Implementation header
⌈The module Implementation source files of the BSW Module shall include its own Implementation header .⌋

OK: [SWS_BSW_00006] Include Memory mapping header
⌈The Implementation source files of the BSW Module shall include the BSW Memory mapping header (<Mip>_MemMap.h).⌋