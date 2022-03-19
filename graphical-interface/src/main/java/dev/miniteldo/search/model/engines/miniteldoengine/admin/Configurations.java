package dev.miniteldo.search.model.engines.miniteldoengine.admin;

public enum Configurations {
    TEXT_FILTER_MODE("parameters", "indexing_text_filter_mode"),
    TEXT_FILTER_VALUE("parameters", "indexing_text_filter_value"),
    TEXT_INDEX_TABLE_SIZE("parameters", "indexing_text_number_table_index"),

    IMAGE_NUM_BITS_QUANTIFICATION("parameters", "indexing_image_quantification"),
    IMAGE_THRESHOLD("parameters", "comparison_image_threshold"),

    AUDIO_SAMPLES("parameters", "indexing_audio_samples"),
    AUDIO_INTERVAL("parameters", "indexing_audio_interval"),
    AUDIO_STEP("parameters", "comparison_audio_step"),
    AUDIO_THRESHOLD("parameters", "comparison_audio_threshold");

    private final String parametersType;
    private final String parameters;

    Configurations(String parametersType, String parameters) {
        this.parametersType = parametersType;
        this.parameters = parameters;
    }

    public String getParametersType() {
        return parametersType;
    }

    public String getParameters() {
        return parameters;
    }
}
