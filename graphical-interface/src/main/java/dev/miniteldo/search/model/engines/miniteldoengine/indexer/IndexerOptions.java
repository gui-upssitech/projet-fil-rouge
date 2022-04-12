package dev.miniteldo.search.model.engines.miniteldoengine.indexer;

public enum IndexerOptions {
    TEXT("indexing", "text"),
    IMAGE("indexing", "image"),
    AUDIO("indexing", "audio"),
    ALL("indexing", "all");

    private String indexingType;
    private String dataType;

    IndexerOptions(String indexingType, String dataType) {
        this.indexingType = indexingType;
        this.dataType = dataType;
    }

    public String getIndexingType() {
        return indexingType;
    }

    public String getDataType() {
        return dataType;
    }
}
