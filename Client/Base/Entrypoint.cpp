#include <Server/Public/Framework.h>

DWORD Main(LPVOID) {

    // Client
    {
        { // Arena (this will only show the arena widget for the arena playlist)
            UFortPlaylistAthena* ArenaPlaylist = UObject::FindObject<UFortPlaylistAthena>("FortPlaylistAthena Playlist_ShowdownAlt_Solo.Playlist_ShowdownAlt_Solo");
            while (!ArenaPlaylist)
                ArenaPlaylist = UObject::FindObject<UFortPlaylistAthena>("FortPlaylistAthena Playlist_ShowdownAlt_Solo.Playlist_ShowdownAlt_Solo");

            FUIExtension ArenaUIExtension;
            ArenaUIExtension.Slot = EUIExtensionSlot::Primary;
            ArenaUIExtension.WidgetClass.ObjectID.AssetPathName = UKismetStringLibrary::Conv_StringToName(TEXT("/Game/UI/Competitive/Arena/ArenaScoringHUD.ArenaScoringHUD_C"));

            ArenaPlaylist->UIExtensions.Add(ArenaUIExtension);
        }
        
        *(bool*)(/* Image base address */ + /* Your GIsClient address */) = true;
        *(bool*)(/* Image base address */ + /* Your GIsServer address */) = false;
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, Main, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
