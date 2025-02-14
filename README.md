# STL2Ascii #
A fast way to generate 3D ASCII animations from STL files.

The program works on a per-facet basis. Hence, For best result, remesh with Blender (https://www.blender.org/) to ensure even distribution of facets.

There is no mem safety, this program is not designed to run in production. It is a template to quickly create 3D ascii animations from STL files. 
In case of seg fault, modify (increase) the setSize parameter.

## note on current build ##
Binary STL format only (which you should be using anyway).
