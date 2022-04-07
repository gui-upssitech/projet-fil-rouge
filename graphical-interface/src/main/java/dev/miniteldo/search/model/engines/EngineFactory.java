package dev.miniteldo.search.model.engines;

import dev.miniteldo.search.model.engines.dummyengine.DummyEngine;
import dev.miniteldo.search.model.engines.miniteldoengine.MiniteldoEngine;

/**
 * class: EngineFactory
 * author: Guillaume Roussin
 * date: 16/03/2022
 *
 * This class helps reduce memory usage of the app
 */
public class EngineFactory {

    // Methods
    public static SearchEngine createEngine(Engines engineType) {
        return switch (engineType) {
            case MINITELDO_ENGINE -> new MiniteldoEngine("search-engine");
            case MINITELDO_ENGINE_2 -> new MiniteldoEngine("search-engine-2");
            case DUMMY_ENGINE -> new DummyEngine();
        };
    }
}