package dev.miniteldo.search.model.engines.miniteldoengine.searcher;

public enum SearcherType {
    IMAGE_COLOR("searcher_image", "color"),
    TEXT_KEYWORD("searcher_text", "keyword"),
    TEXT_PATH("searcher_text", "text"),
    IMAGE_RGB_PATH("searcher_image", "color"),
    IMAGE_NB_PATH("searcher_image", "gray"),
    AUDIO_PATH("searcher_audio", "audio");

    private final String searcherType;
    private final String dataType;

    SearcherType(String searcherType, String dataType) {
        this.searcherType = searcherType;
        this.dataType = dataType;
    }

    public String getSearcherType() {
        return searcherType;
    }

    public String getDataType() {
        return dataType;
    }
}