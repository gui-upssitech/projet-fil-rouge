module com.example.demo {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.kordamp.bootstrapfx.core;

    opens com.miniteldo to javafx.fxml;
    exports com.miniteldo;
}