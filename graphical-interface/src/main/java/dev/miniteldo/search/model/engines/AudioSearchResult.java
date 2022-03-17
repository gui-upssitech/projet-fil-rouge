package dev.miniteldo.search.model.engines;

public class AudioSearchResult extends SearchResult {

    private int timeCode;

    public AudioSearchResult(String filePath, float confidence, int timeCode) {
        super(filePath, confidence);
        this.timeCode = timeCode;
    }

    @Override
    public String toString() {
        return "{" +
                "filePath='" + filePath + '\'' +
                ", confidence=" + confidence +
                ", timeCode=" + timeCode +
                '}';
    }
}
