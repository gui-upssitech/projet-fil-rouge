package dev.miniteldo.search.model.engines.miniteldoengine.admin;

public enum LoggerOptions {
    NEW_PASSWORD("log", "reset"),
    LOGIN("log", "login");

    private String logType;
    private String logAction;

    LoggerOptions(String logType, String logAction) {
        this.logType = logType;
        this.logAction = logAction;
    }

    public String getLogType() {
        return logType;
    }

    public String getLogAction() {
        return logAction;
    }
}
