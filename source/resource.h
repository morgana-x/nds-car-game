#include <NEMain.h>

typedef struct{
    int numMaterials;
    const char* LoadedMaterialsPaths[30];
    NE_Material *LoadedMaterials[30];
}ResourceManager;
static ResourceManager resourceManager;
NE_Material* Resource_LoadMaterial( const char* path, int width, int height );
NE_Material* Resource_LoadMaterialTransperant( const char* path, int width, int height );
NE_Material* Resource_LoadMaterial_Advanced( const char* path, int width, int height, NE_TextureFormat format);

NE_Material *Resource_FetchMaterial(int index);
void Resource_Init();