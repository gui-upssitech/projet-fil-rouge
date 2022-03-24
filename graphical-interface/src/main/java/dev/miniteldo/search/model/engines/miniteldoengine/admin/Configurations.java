package dev.miniteldo.search.model.engines.miniteldoengine.admin;

public enum Configurations {
    INDEXING_MODE("parameters", "indexing_mode", 0, 1),

    TEXT_FILTER_MODE("parameters", "indexing_text_filter_mode", 0, 1),
    TEXT_FILTER_VALUE("parameters", "indexing_text_filter_value", 3, 30),
    TEXT_INDEX_TABLE_SIZE("parameters", "indexing_text_number_table_index", 3, 30),
    TEXT_INDEX_DEBUG("parameters", "indexing_text_debug", 0, 1),

    IMAGE_NUM_BITS_QUANTIFICATION("parameters", "indexing_image_quantification", 1, 5),
    IMAGE_THRESHOLD("parameters", "comparison_image_threshold", 0, 100),

    AUDIO_SAMPLES("parameters", "indexing_audio_samples", 256, 8192),
    AUDIO_INTERVAL("parameters", "indexing_audio_interval", 3, 1000),
    AUDIO_STEP("parameters", "comparison_audio_step", 1, 10),
    AUDIO_THRESHOLD("parameters", "comparison_audio_threshold", 0, 100);

    private final String parametersType;
    private final String parameters;
    private final int min;
    private final int max;

    Configurations(String parametersType, String parameters, int min, int max) {
        this.parametersType = parametersType;
        this.parameters = parameters;
        this.min = min;
        this.max = max;
    }

    public static Configurations getConfiguration(String parameters) {
        for(Configurations configuration : values()) {
            if(configuration.parameters.equals(parameters)) {
                return configuration;
            }
        }
        return null;
    }

    public String getParametersType() {
        return parametersType;
    }

    public String getParameters() {
        return parameters;
    }

    public int getMin() {
        return min;
    }

    public int getMax() {
        return max;
    }
}
