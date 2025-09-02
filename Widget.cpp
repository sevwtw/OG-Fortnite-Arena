// You make a DLL C++ project with your CppSDK from Dumper-7 (You dump the game version you want with Dumper-7 for the SDK)
{
    { // Arena
        UFortPlaylistAthena* ArenaPlaylist = UObject::FindObject<UFortPlaylistAthena>("FortPlaylistAthena Playlist_ShowdownAlt_Solo.Playlist_ShowdownAlt_Solo");
        while (!ArenaPlaylist) // Just loops until found
            ArenaPlaylist = UObject::FindObject<UFortPlaylistAthena>("FortPlaylistAthena Playlist_ShowdownAlt_Solo.Playlist_ShowdownAlt_Solo");

        FUIExtension ArenaUIExtension;
        ArenaUIExtension.Slot = EUIExtensionSlot::Primary;
        ArenaUIExtension.WidgetClass.ObjectID.AssetPathName = UKismetStringLibrary::Conv_StringToName(TEXT("/Game/UI/Competitive/Arena/ArenaScoringHUD.ArenaScoringHUD_C")); // This is the global asset path for Arena

        ArenaPlaylist->UIExtensions.Add(ArenaUIExtension);
    }

    *(bool*)(/* Image base address */ + /* Your GIsClient address */) = true;
    *(bool*)(/* Image base address */ + /* Your GIsServer address */) = false;
}
