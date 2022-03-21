package dev.miniteldo.search.model.engines.miniteldoengine.indexer;

public enum IndexerMode {
    UPDATE("update"),
    RESET("reset");

    private final String mode;

    IndexerMode(String mode) {
        this.mode = mode;
    }

    public String getMode() {
        return mode;
    }
}
