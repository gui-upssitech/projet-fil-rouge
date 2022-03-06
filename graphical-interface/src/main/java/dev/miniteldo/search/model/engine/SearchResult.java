package dev.miniteldo.search.model.engine;

/**
 * Class: SearchResult
 * Auteurs: Team Miniteldo
 */
public class SearchResult {

    // Attributes
    private final String filePath;
    private final float confidence;

    // Constructor
    public SearchResult(String filePath, float confidence) {
        this.filePath = filePath;
        this.confidence = confidence;
    }

    // Methods
    public String getFilePath() {
        return filePath;
    }

    public float getConfidence() {
        return confidence;
    }

}