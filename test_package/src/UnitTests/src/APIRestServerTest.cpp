/*
 * APIRestServerTest.cpp
 *
 *  Created on: 11 de mai. de 2026
 *      Author: marcus.chaves
 */

#include "../include/APIRestServerTest.h"

#include <Poco/Net/HTTPServerRequestImpl.h>
#include <Poco/Net/FilePartSource.h>
#include <Poco/Net/HTTPServerResponseImpl.h>

#include "../../../../src/APIRestRequestHandlerFactory.h"

void APIRestServerTest::teste_rota_signature() {
    Poco::Net::HTTPServerRequestImpl request;
    request.setURI("/signature");
    Poco::Net::HTMLForm form;
    form.setEncoding(Poco::Net::HTMLForm::ENCODING_MULTIPART);
    form.addPart("File-To-Assign", new Poco::Net::FilePartSource("doc.txt"));
    form.addPart("Certificate", new Poco::Net::FilePartSource("certificado_teste_hub.pfx"));
    form.add("Password", "bry123456");
    form.prepareSubmit(request);
    Poco::Net::HTTPServerResponseImpl response;
    APIRestRequestHandlerFactory factory("upload");
    factory.createRequestHandler(request);
}

