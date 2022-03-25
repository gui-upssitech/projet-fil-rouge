package dev.miniteldo.search.controller;

// Project : graphical-interface

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurations;
import dev.miniteldo.search.model.engines.miniteldoengine.indexer.IndexerMode;
import dev.miniteldo.search.model.engines.miniteldoengine.openedclosedmode.OpenedClosedMode;
import dev.miniteldo.search.model.tools.FileTools;
import dev.miniteldo.search.view.Dialog;
import dev.miniteldo.search.view.Views;
import javafx.beans.value.ChangeListener;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.util.ArrayList;
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
    public Label labelIndexation;

    // Text componenent
    private ArrayList<String> stringsComboMode;
    public ComboBox<String> cbTextMode;
    public Spinner<Integer> spTextThreshold;
    public Spinner<Integer> spTextIndex;
    private ArrayList<String> stringsComboDebug;
    public ComboBox<String> cbTextDebug;

    private ArrayList<String> stringsComboModeOpen;
    public ComboBox<String> cbModeOpen;

    // Image componenent
    public Spinner<Integer> spImageBit;
    public Spinner<Integer> spImageThreshold;

    // Audio componenent
    public Spinner<Integer> spAudioSample;
    public Spinner<Integer> spAudioInterval;
    public Spinner<Integer> spAudioStep;
    public Spinner<Integer> spAudioThreshold;

    private HashMap<Configurations, Integer> hashMapOldValue;
    private HashMap<Configurations, Integer> hashMapNewValue = new HashMap<>();
    private HashMap<Configurations, Spinner<Integer>> hashMapSpinner = new HashMap<>();

    private boolean isTextModified = false;
    private boolean isImageModified = false;
    private boolean isAudioModified = false;


    @FXML
    public void initialize() {
        // Init configuration value from C code
        this.hashMapOldValue = AppState.getInstance().getEngine().loadConfigs();
        System.out.println(hashMapOldValue);

        // Init comboBox String
        stringsComboMode = new ArrayList<>();
        stringsComboMode.add("Limite");
        stringsComboMode.add("Seuil");

        stringsComboDebug = new ArrayList<>();
        stringsComboDebug.add("Non");
        stringsComboDebug.add("Oui");

        stringsComboModeOpen = new ArrayList<>();
        stringsComboModeOpen.add("Fermé");
        stringsComboModeOpen.add("Ouvert");

        // Add strings to comboBox
        cbTextMode.setItems(FXCollections.observableArrayList(stringsComboMode));
        cbTextDebug.setItems(FXCollections.observableArrayList(stringsComboDebug));
        cbModeOpen.setItems(FXCollections.observableArrayList(stringsComboModeOpen));

        initData();

        // Set spinner with config value from C
        for (Map.Entry<Configurations, Spinner<Integer>> entry : hashMapSpinner.entrySet()) {
            initSpinner(entry.getValue(), entry.getKey());
        }

        updateVisibilitySpinner();

    }

    /**
     * Init the hashmap of spinner
     */
    public void initData() {
        // Text
        this.hashMapSpinner.put(Configurations.TEXT_FILTER_VALUE, spTextThreshold);
        this.hashMapSpinner.put(Configurations.TEXT_INDEX_TABLE_SIZE, spTextIndex);
        // Mode
        this.cbTextMode.getSelectionModel().select(stringsComboMode.get(hashMapOldValue.get(Configurations.TEXT_FILTER_MODE)));
        this.cbTextDebug.getSelectionModel().select(stringsComboDebug.get(hashMapOldValue.get(Configurations.TEXT_INDEX_DEBUG)));
        this.cbModeOpen.getSelectionModel().select(stringsComboModeOpen.get(hashMapOldValue.get(Configurations.INDEXING_MODE)));

        // Image
        this.hashMapSpinner.put(Configurations.IMAGE_NUM_BITS_QUANTIFICATION, spImageBit);
        this.hashMapSpinner.put(Configurations.IMAGE_THRESHOLD, spImageThreshold);

        // Audio
        this.hashMapSpinner.put(Configurations.AUDIO_SAMPLES, spAudioSample);
        this.hashMapSpinner.put(Configurations.AUDIO_INTERVAL, spAudioInterval);
        this.hashMapSpinner.put(Configurations.AUDIO_STEP, spAudioStep);
        this.hashMapSpinner.put(Configurations.AUDIO_THRESHOLD, spAudioThreshold);
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
        this.hashMapNewValue.put(Configurations.TEXT_FILTER_VALUE, spTextThreshold.getValue());
        this.hashMapNewValue.put(Configurations.TEXT_INDEX_TABLE_SIZE, spTextIndex.getValue());
        // mode
        this.hashMapNewValue.put(Configurations.TEXT_FILTER_MODE, cbTextMode.getSelectionModel().getSelectedIndex());
        this.hashMapNewValue.put(Configurations.TEXT_INDEX_DEBUG, cbTextDebug.getSelectionModel().getSelectedIndex());
        this.hashMapNewValue.put(Configurations.INDEXING_MODE, cbModeOpen.getSelectionModel().getSelectedIndex());

        // Image
        this.hashMapNewValue.put(Configurations.IMAGE_NUM_BITS_QUANTIFICATION, spImageBit.getValue());
        this.hashMapNewValue.put(Configurations.IMAGE_THRESHOLD, spImageThreshold.getValue());

        // Audio
        this.hashMapNewValue.put(Configurations.AUDIO_SAMPLES, spAudioSample.getValue());
        this.hashMapNewValue.put(Configurations.AUDIO_INTERVAL, spAudioInterval.getValue());
        this.hashMapNewValue.put(Configurations.AUDIO_STEP, spAudioStep.getValue());
        this.hashMapNewValue.put(Configurations.AUDIO_THRESHOLD, spAudioThreshold.getValue());
    }

    @FXML
    protected void onComboBoxModeAction() {
        updateVisibilitySpinner();
    }

    private void updateVisibilitySpinner() {
        boolean showThreshold = cbTextMode.getSelectionModel().getSelectedIndex() == 0;
        spTextIndex.setDisable(!showThreshold);
        spTextThreshold.setDisable(showThreshold);

        if (showThreshold) {
            spTextThreshold.getValueFactory().setValue(hashMapOldValue.get(Configurations.TEXT_FILTER_VALUE));
        } else {
            spTextIndex.getValueFactory().setValue(hashMapOldValue.get(Configurations.TEXT_INDEX_TABLE_SIZE));
        }
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
                        AppState.getInstance().getEngine().setConfig(Configurations.AUDIO_SAMPLES, spAudioSample.getValue());
                        checkModifiedType(config); // check the type modified
                    }
                } else {
                    if (config.equals(Configurations.INDEXING_MODE)) {
                        if(newValue == 0) {
                            OpenedClosedMode.stop();
                        } else {
                            OpenedClosedMode.start();
                        }
                    }
                    AppState.getInstance().getEngine().setConfig(config, newValue);
                    checkModifiedType(config); // check the type modified
                }
                System.out.println(config);
            }
        }

        // call indexing function
        if (isTextModified) {
            AppState.getInstance().getEngine().indexText(IndexerMode.RESET);
        }
        if (isImageModified) {
            AppState.getInstance().getEngine().indexImage(IndexerMode.RESET);
        }
        if (isAudioModified) {
            AppState.getInstance().getEngine().indexAudio(IndexerMode.RESET);
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
        String type = configurations.toString().split("_")[0];

        switch (type) {
            case "TEXT":
                isTextModified = true;
                break;

            case "IMAGE":
                isImageModified = true;
                break;

            case "AUDIO":
                isAudioModified = true;
                break;
        }
    }

    /**
     * Doit être une puissance de 2 => audio samples
     */
    private boolean verificationAudioParam(int n) {
        double v = Math.log(n) / Math.log(2);
        return (int) (Math.ceil(v)) == (int) (Math.floor(v));
    }


    // Methods
    @FXML
    protected void onReturnButton() {
        App.setView(Views.PARAMETERS);
    }

    @FXML
    protected void onValidButton() {
        labelIndexation.setText("Indexation en cours ...");
        saveConfiguration();
        labelIndexation.setText("Indexation fini !");
        App.showDialog(Dialog.SUCCESS);
    }

    public void onResetButton(ActionEvent event) {
        // Delete the file content
        boolean isClear = FileTools.clearFile();

        if (isClear) {
            App.showDialog(Dialog.SUCCESS);
        } else {
            App.showDialog(Dialog.ERROR);
        }
    }
}
