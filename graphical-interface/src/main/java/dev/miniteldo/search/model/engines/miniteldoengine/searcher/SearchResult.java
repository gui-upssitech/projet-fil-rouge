package dev.miniteldo.search.model.engines.miniteldoengine.searcher;

public class SearchResult {
        private String filePath;
        private float confidence;

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
                return "SearchResult{" +
                        "filePath='" + filePath + '\'' +
                        ", confidence=" + confidence +
                        '}';
        }
}
