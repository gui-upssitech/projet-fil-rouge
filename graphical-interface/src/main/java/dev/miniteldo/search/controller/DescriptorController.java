package dev.miniteldo.search.controller;

// Project : graphical-interface

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.AudioDescriptor;
import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.Descriptor;
import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.ImageDescriptor;
import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.TextDescriptor;
import dev.miniteldo.search.model.tools.FileTools;
import dev.miniteldo.search.view.SearchResultComponentFactory;
import dev.miniteldo.search.view.enums.Component;
import dev.miniteldo.search.view.enums.Dialog;
import dev.miniteldo.search.view.enums.Views;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Label;
import javafx.scene.control.Spinner;
import javafx.scene.control.SpinnerValueFactory;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

/**
 * Classe DescriptorController ...
 * Date : 27/03/2022
 * Auteur : Julian
 */
public class DescriptorController {
    // Attributs
    public TextField fileField;
    public VBox descriptorContainer;
    public Spinner<Double> spinner;
    public Label labelTime;
    public TextField idTextField;

    private Descriptor d;
    private HashMap<String, String> descriptorText;
    private int[] descriptorImage;

    @FXML
    public void initialize() {
        fileField.textProperty().addListener((observable, oldValue, newValue) -> {
            d = AppState.getInstance().getEngine().viewDescriptor(fileField.getText());
            if (d instanceof AudioDescriptor audioDescriptor) {
                SpinnerValueFactory.DoubleSpinnerValueFactory valueFactory = new SpinnerValueFactory.DoubleSpinnerValueFactory(0, audioDescriptor.getDuration(), 0.1);
                valueFactory.setAmountToStepBy(0.1);
                spinner.setValueFactory(valueFactory);
            }

            spinner.setVisible(d instanceof AudioDescriptor);
            labelTime.setVisible(d instanceof AudioDescriptor);
        });

        spinner.valueProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue <= ((AudioDescriptor) d).getDuration()) {
                onVisualiserAction();
            }
        });
    }

    public void onReturnButton(MouseEvent mouseEvent) {
        App.setView(Views.ADMIN_CONFIG);
    }

    public void onKeyAction(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ESCAPE)) {
            App.setView(Views.ADMIN_CONFIG);
        }
    }

    public void onFileButton(ActionEvent event) {
        Stage stage = (Stage) fileField.getScene().getWindow();
        File file = FileTools.getInputFile(stage);

        if (file != null) {
            fileField.setText(file.toString());
        }
    }

    public void onVisualiserAction() {
        if (fileField.getText().isBlank()) {
            App.showDialog(Dialog.ERROR, "Problème, la requête est vide");
        } else {
            descriptorContainer.getChildren().clear();

            d = AppState.getInstance().getEngine().viewDescriptor(fileField.getText());

            // Error !
            if (d == null){
                App.showDialog(Dialog.ERROR, "Fichier inconnu !");
            }else {
                idTextField.setText(d.getId());

                if (d instanceof TextDescriptor textDescriptor) {
                    descriptorText = textDescriptor.getDataDescriptor();

                    for (Map.Entry<String, String> entry : descriptorText.entrySet()) {
                        System.out.println(entry.getKey() + "/" + entry.getValue());

                        HBox result = createComponent(entry.getKey(), entry.getValue());

                        descriptorContainer.getChildren().add(result);
                    }
                } else if (d instanceof ImageDescriptor imageDescriptor) {
                    descriptorImage = imageDescriptor.getHistogram();
                    System.out.println(imageDescriptor.getMax());

                    BarChart<String, Number> result = createChart(descriptorImage);
                    descriptorContainer.getChildren().add(result);

                } else if (d instanceof AudioDescriptor audioDescriptor) {
                    int index = audioDescriptor.findIdxByTimeCode(spinner.getValue().floatValue());
                    int[] tab = audioDescriptor.getHistograms()[index];

                    BarChart<String, Number> result = createChart(tab);
                    descriptorContainer.getChildren().add(result);
                }
            }

        }
    }

    private HBox createComponent(String word, String value) {
        HBox root;
        String componentPath = "/layout/" + Component.DESCRIPTOR.getPath();
        FXMLLoader fxmlLoader = new FXMLLoader(SearchResultComponentFactory.class.getResource(componentPath));

        try {
            root = (HBox) fxmlLoader.load();

            Label wordLabel = (Label) root.lookup("#wordLabel");
            Label valueLabel = (Label) root.lookup("#valueLabel");

            wordLabel.setText(word);
            valueLabel.setText(value);

        } catch (IOException e) {
            root = new HBox();
        }

        return root;
    }

    private BarChart<String, Number> createChart(int[] data) {
        CategoryAxis xAxis = new CategoryAxis();
        if (d instanceof ImageDescriptor) {
            xAxis.setLabel("Pixel quantifié"); // Image
        } else if (d instanceof AudioDescriptor) {
            xAxis.setLabel("Niveau échantillonné"); // Audio
        }

        NumberAxis yAxis = new NumberAxis();
        yAxis.setLabel("Occurrence");// Image & Audio

        // Create a BarChart
        BarChart<String, Number> barChart = new BarChart<>(xAxis, yAxis);

        // Series 1 - Data of 2014
        XYChart.Series<String, Number> dataSerie = new XYChart.Series<>();

        for (int i = 0; i < data.length; i++) {
            dataSerie.getData().add(new XYChart.Data<>(String.valueOf(i), data[i]));
        }

        // Add Series to BarChart.
        barChart.getData().add(dataSerie);
        barChart.setLegendVisible(false);
        barChart.setTitle("Histogramme");

        return barChart;
    }
}
