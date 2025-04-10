#include "resource.h"
#include "string.h"

NE_Material* Resource_LoadMaterial( const char* path, int width, int height ) {
    for (size_t i = 0; i < resourceManager.numMaterials; i++)
    {
        if ( strcmp(resourceManager.LoadedMaterialsPaths[i], path) == 0)
        {
            //printf("We already loaded %s\n", path);
            return resourceManager.LoadedMaterials[i];
        }
    }
    if (resourceManager.numMaterials > 20)
    {
        printf("Error too many materials loaded!\n");
        return 0;
    }

    NE_Material *Material = NE_MaterialCreate();
    NE_MaterialTexLoadFAT(Material, NE_RGB5, width, height, NE_TEXGEN_TEXCOORD,
        path);

    int index = resourceManager.numMaterials;
    resourceManager.LoadedMaterials[index] = Material;
    resourceManager.LoadedMaterialsPaths[index] = path;
    resourceManager.numMaterials++;
  //  printf("Loaded %s to %i\n", path, index);
    return Material;
}

NE_Material *Resource_FetchMaterial(int index)
{
    if (index > resourceManager.numMaterials) return 0;
    return resourceManager.LoadedMaterials[index]; 
}
void Resource_Init()
{
    //resourceManager = calloc(1, sizeof( ResourceManager));
    resourceManager.numMaterials = 0;
}