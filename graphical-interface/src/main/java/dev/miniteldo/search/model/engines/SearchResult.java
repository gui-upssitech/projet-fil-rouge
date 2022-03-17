package dev.miniteldo.search.model.engines;

public class SearchResult {
    protected String filePath;
    protected float confidence;

    public SearchResult(String filePath, float confidence) {
        this.filePath = filePath;
        this.confidence = confidence;
    }

    public String getFilePath() {
        return filePath;
    }

    public float getConfidence() {
        return confidence;
    }

    @Override
    public String toString() {
        return "{" +
                "filePath='" + filePath + '\'' +
                ", confidence=" + confidence +
                '}';
    }
}
