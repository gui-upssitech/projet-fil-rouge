package dev.miniteldo.search.model.engines.miniteldoengine.admin;

public enum LogOptions {
    NEW_PASSWORD("todo"),
    LOGIN("login");

    private String logType;

    LogOptions(String logType) {
        this.logType = logType;
    }

    public String getLogType() {
        return logType;
    }
}
