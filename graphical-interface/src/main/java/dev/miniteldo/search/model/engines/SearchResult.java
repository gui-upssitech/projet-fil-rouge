package dev.miniteldo.search.model.engines;

import java.util.Objects;

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

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        SearchResult that = (SearchResult) o;
        return Objects.equals(filePath, that.filePath);
    }

    @Override
    public int hashCode() {
        return Objects.hash(filePath);
    }
}
