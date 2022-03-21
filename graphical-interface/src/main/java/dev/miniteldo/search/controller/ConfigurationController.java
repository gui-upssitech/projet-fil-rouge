package dev.miniteldo.search.controller;

// Project : graphical-interface

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurations;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;
import dev.miniteldo.search.view.Views;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.image.ImageView;

import java.util.HashMap;

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

    private HashMap<Configurations, Integer> hashMap;

    public ToggleButton debugButton;

    public ImageView loadingGif;

    @FXML
    public void initialize() {
        loadingGif.setVisible(false);

        // Init configuration value from C code
        this.hashMap = AppState.getInstance().getEngine().loadConfigs();
        System.out.println(hashMap);

        comboBoxMode.setItems(FXCollections.observableArrayList(Configurations.values()));

        // Set spinner with config value from C
        initSpinner(spinnerTextValue, Configurations.TEXT_FILTER_VALUE, hashMap.get(Configurations.TEXT_FILTER_VALUE));
        initSpinner(spinnerIndexText, Configurations.TEXT_INDEX_TABLE_SIZE, hashMap.get(Configurations.TEXT_INDEX_TABLE_SIZE));

        initSpinner(spinnerBitQuanti, Configurations.IMAGE_NUM_BITS_QUANTIFICATION, hashMap.get(Configurations.IMAGE_NUM_BITS_QUANTIFICATION));

        initSpinner(spinnerEchantillon, Configurations.AUDIO_SAMPLES, hashMap.get(Configurations.AUDIO_SAMPLES));
        initSpinner(spinnerInterval, Configurations.AUDIO_INTERVAL, hashMap.get(Configurations.AUDIO_INTERVAL));
    }

    private void initSpinner(Spinner<Integer> spinner, Configurations configurations, int init) {
        SpinnerValueFactory<Integer> valueFactory =
                new SpinnerValueFactory.IntegerSpinnerValueFactory(
                        configurations.getMin(),
                        configurations.getMax(),
                        init);
        spinner.setValueFactory(valueFactory);
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

//        loadingGif.setVisible(true);

        saveConfiguration();

//        loadingGif.setVisible(false);
        labelIndexation.setText("Indexation fini !");
    }

    private void saveConfiguration() {
        // look
        // vérif les valeurs changées + domaine text/image/audio
        // reset text => suprimme et recréer

        // FIXME: 21/03/2022 FIX AND OPTIMIS THIS SHIT
        if (!hashMap.get(Configurations.TEXT_FILTER_VALUE).equals(spinnerTextValue.getValue())) {
            AppState.getInstance().getEngine().setConfig(Configurations.TEXT_FILTER_VALUE, spinnerTextValue.getValue());
            System.out.println("Text value modifié");
        }
        if (!hashMap.get(Configurations.TEXT_INDEX_TABLE_SIZE).equals(spinnerIndexText.getValue())) {
            AppState.getInstance().getEngine().setConfig(Configurations.TEXT_INDEX_TABLE_SIZE, spinnerIndexText.getValue());
            System.out.println("Index modifié");
        }
        if (!hashMap.get(Configurations.IMAGE_NUM_BITS_QUANTIFICATION).equals(spinnerBitQuanti.getValue())) {
            AppState.getInstance().getEngine().setConfig(Configurations.IMAGE_NUM_BITS_QUANTIFICATION, spinnerBitQuanti.getValue());
            System.out.println("Bit de quantification changé");
        }
        if (!hashMap.get(Configurations.AUDIO_INTERVAL).equals(spinnerInterval.getValue())) {
            AppState.getInstance().getEngine().setConfig(Configurations.AUDIO_INTERVAL, spinnerInterval.getValue());
            System.out.println("Interval modifié");
        }
        if (!hashMap.get(Configurations.AUDIO_SAMPLES).equals(spinnerEchantillon.getValue())) {
            if (verificationAudioParam(spinnerEchantillon.getValue())) {
                AppState.getInstance().getEngine().setConfig(Configurations.AUDIO_SAMPLES, spinnerEchantillon.getValue());
            }
            System.out.println("Echantillon modifié");
        }
    }

    /**
     * Doit etre une puissance de 2 => audio samples
     */
    private boolean verificationAudioParam(int n) {
        return (int) (Math.ceil((Math.log(n) / Math.log(2))))
                == (int) (Math.floor(((Math.log(n) / Math.log(2)))));
    }
}
