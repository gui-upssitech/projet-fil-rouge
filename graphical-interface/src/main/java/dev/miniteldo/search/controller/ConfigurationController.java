package dev.miniteldo.search.controller;

// Project : graphical-interface

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurations;
import dev.miniteldo.search.model.engines.miniteldoengine.indexer.IndexerMode;
import dev.miniteldo.search.view.Views;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.image.ImageView;

import java.util.HashMap;
import java.util.Map;

/**
 * Classe ConfigurationController ...
 * Date : 02/03/2022
 * Auteur : Julian
 */
public class ConfigurationController {
    // Attributs components
    public Button validButton;
    public ProgressBar progressBar;
    public Label labelIndexation;
    public Button returnButton;
    public ComboBox<Configurations> comboBoxMode;

    public Spinner<Integer> spinnerTextValue;
    public Spinner<Integer> spinnerIndexText;
    public Spinner<Integer> spinnerEchantillon;
    public Spinner<Integer> spinnerInterval;
    public Spinner<Integer> spinnerBitQuanti;

    private HashMap<Configurations, Integer> hashMapOldValue;
    private HashMap<Configurations, Integer> hashMapNewValue = new HashMap<>();
    private HashMap<Configurations, Spinner<Integer>> hashMapSpinner = new HashMap<>();

    private boolean isTextModified = false;
    private boolean isImageModified = false;
    private boolean isAudioModified = false;

    public ToggleButton debugButton;

    public ImageView loadingGif;

    @FXML
    public void initialize() {
        loadingGif.setVisible(false);

        // Init configuration value from C code
        this.hashMapOldValue = AppState.getInstance().getEngine().loadConfigs();
        System.out.println(hashMapOldValue);

        comboBoxMode.setItems(FXCollections.observableArrayList(Configurations.values()));

        initHashMapSpinner();

        // Set spinner with config value from C
        for (Map.Entry<Configurations, Spinner<Integer>> entry : hashMapSpinner.entrySet()) {
            initSpinner(entry.getValue(), entry.getKey());
        }
    }

    /**
     * Init the hashmap of spinner
     */
    public void initHashMapSpinner() {
        // Text
        this.hashMapSpinner.put(Configurations.TEXT_FILTER_VALUE, spinnerTextValue);
        this.hashMapSpinner.put(Configurations.TEXT_INDEX_TABLE_SIZE, spinnerIndexText);

        // Image
        this.hashMapSpinner.put(Configurations.IMAGE_NUM_BITS_QUANTIFICATION, spinnerBitQuanti);

        // Audio
        this.hashMapSpinner.put(Configurations.AUDIO_SAMPLES, spinnerEchantillon);
        this.hashMapSpinner.put(Configurations.AUDIO_INTERVAL, spinnerInterval);
    }

    /**
     * Set the min, max and init of a spinner
     *
     * @param spinner
     * @param configurations
     */
    private void initSpinner(Spinner<Integer> spinner, Configurations configurations) {
        SpinnerValueFactory<Integer> valueFactory = new SpinnerValueFactory.IntegerSpinnerValueFactory(configurations.getMin(), configurations.getMax(), hashMapOldValue.get(configurations));
        spinner.setValueFactory(valueFactory);
    }

    /**
     * Get all value from spinner and put it in the correct map
     */
    private void getAllSpinnerValueToMap() {
        // Text
        this.hashMapNewValue.put(Configurations.TEXT_FILTER_VALUE, spinnerTextValue.getValue());
        this.hashMapNewValue.put(Configurations.TEXT_INDEX_TABLE_SIZE, spinnerIndexText.getValue());

        // Image
        this.hashMapNewValue.put(Configurations.IMAGE_NUM_BITS_QUANTIFICATION, spinnerBitQuanti.getValue());

        // Audio
        this.hashMapNewValue.put(Configurations.AUDIO_SAMPLES, spinnerEchantillon.getValue());
        this.hashMapNewValue.put(Configurations.AUDIO_INTERVAL, spinnerInterval.getValue());
    }

    private void saveConfiguration() {
        // Get all value from spinner
        getAllSpinnerValueToMap();

        // Comparison of old and new value of all spinner
        for (Map.Entry<Configurations, Integer> entry : hashMapOldValue.entrySet()) {
            Configurations config = entry.getKey();
            Integer oldValue = entry.getValue();
            Integer newValue = hashMapNewValue.get(config);

            if (!oldValue.equals(newValue) && newValue != null) {
                // Audio sample need vérification
                if (config.equals(Configurations.AUDIO_SAMPLES)) {
                    if (verificationAudioParam(newValue)) {
                        AppState.getInstance().getEngine().setConfig(Configurations.AUDIO_SAMPLES, spinnerEchantillon.getValue());
                        checkModifiedType(config); // check the type modified
                    }
                } else {
                    AppState.getInstance().getEngine().setConfig(config, newValue);
                }

                System.out.println(config);
            }
        }

        // call indexing function
        if (isTextModified) {
            AppState.getInstance().getEngine().indexText(IndexerMode.RESET);
        }
        if (isImageModified) {
            AppState.getInstance().getEngine().indexText(IndexerMode.RESET);
        }
        if (isAudioModified) {
            AppState.getInstance().getEngine().indexText(IndexerMode.RESET);
        }

        // Reset value
        this.hashMapOldValue = AppState.getInstance().getEngine().loadConfigs();
        isTextModified = false;
        isImageModified = false;
        isAudioModified = false;

        System.out.println("====");
        System.out.println("Fini ! ");
        System.out.println("====");
    }

    /**
     * For the param config fix to true the correct modified value
     *
     * @param configurations
     */
    public void checkModifiedType(Configurations configurations) {
        String type = configurations.getParametersType().split("_")[0];

        switch (type) {
            case "TEXT":
                isTextModified = true;
                break;
            case "IMAGE":
                isImageModified = true;
                break;
            default:
                isAudioModified = true;
                break;
        }
    }

    /**
     * Doit être une puissance de 2 => audio samples
     */
    private boolean verificationAudioParam(int n) {
        return (int) (Math.ceil((Math.log(n) / Math.log(2)))) == (int) (Math.floor(((Math.log(n) / Math.log(2)))));
    }


    // Methods
    @FXML
    protected void onReturnButton() {
        App.setView(Views.PARAMETERS);
    }

    @FXML
    protected void onValidButton() {
        labelIndexation.setText("Indexation en cours ...");
        progressBar.setProgress(ProgressBar.INDETERMINATE_PROGRESS);

        loadingGif.setVisible(true);

        saveConfiguration();

        loadingGif.setVisible(false);
        labelIndexation.setText("Indexation fini !");
    }

}
