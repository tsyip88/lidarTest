TEMPLATE = subdirs

SUBDIRS += src \
    app/app

CONFIG(debug, debug) {
    SUBDIRS += tests
}
