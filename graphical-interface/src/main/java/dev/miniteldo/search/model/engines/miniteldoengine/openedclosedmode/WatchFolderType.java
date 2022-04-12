package dev.miniteldo.search.model.engines.miniteldoengine.openedclosedmode;

public enum WatchFolderType {
    TEXT("text"),
    NB_IMAGE("image/NB"),
    RGB_IMAGE("image/RGB"),
    AUDIO("audio");

    private String type;

    WatchFolderType(String type) {
        this.type = type;
    }

    public String getType() {
        return type;
    }
}
