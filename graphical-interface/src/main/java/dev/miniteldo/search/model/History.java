package dev.miniteldo.search.model;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Classe History ...
 * Date : 09/04/2022
 * Auteur : Julian
 */
public class History implements Comparable<History> {
    // Attributs
    private final String request;
    private final Date date;

    // Contructor
    public History(String request, Date date) {
        this.request = request;
        this.date = date;
    }

    // Getters
    public String getRequest() {
        return request;
    }

    public Date getDate() {
        return date;
    }

    @Override
    public int compareTo(History o) {
        if (date.equals(o.getDate())) {
            return 0;
        } else if (date.before(o.getDate())) {
            return 1;
        } else {
            return -1;
        }
    }

    @Override
    public String toString() {
        SimpleDateFormat formatter = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
        return request + " - " + formatter.format(date);
    }

}
