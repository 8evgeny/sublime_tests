/* soapMessengerServiceSoapBindingProxy.cpp
   Generated by gSOAP 2.8.74 for duplo.h

gSOAP XML Web services tools
Copyright (C) 2000-2018, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapMessengerServiceSoapBindingProxy.h"

MessengerServiceSoapBindingProxy::MessengerServiceSoapBindingProxy()
{	this->soap = soap_new();
	this->soap_own = true;
	MessengerServiceSoapBindingProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

MessengerServiceSoapBindingProxy::MessengerServiceSoapBindingProxy(const MessengerServiceSoapBindingProxy& rhs)
{	this->soap = rhs.soap;
	this->soap_own = false;
	this->soap_endpoint = rhs.soap_endpoint;
}

MessengerServiceSoapBindingProxy::MessengerServiceSoapBindingProxy(struct soap *_soap)
{	this->soap = _soap;
	this->soap_own = false;
	MessengerServiceSoapBindingProxy_init(_soap->imode, _soap->omode);
}

MessengerServiceSoapBindingProxy::MessengerServiceSoapBindingProxy(struct soap *_soap, const char *soap_endpoint_url)
{	this->soap = _soap;
	this->soap_own = false;
	MessengerServiceSoapBindingProxy_init(_soap->imode, _soap->omode);
	soap_endpoint = soap_endpoint_url;
}

MessengerServiceSoapBindingProxy::MessengerServiceSoapBindingProxy(const char *soap_endpoint_url)
{	this->soap = soap_new();
	this->soap_own = true;
	MessengerServiceSoapBindingProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
	soap_endpoint = soap_endpoint_url;
}

MessengerServiceSoapBindingProxy::MessengerServiceSoapBindingProxy(soap_mode iomode)
{	this->soap = soap_new();
	this->soap_own = true;
	MessengerServiceSoapBindingProxy_init(iomode, iomode);
}

MessengerServiceSoapBindingProxy::MessengerServiceSoapBindingProxy(const char *soap_endpoint_url, soap_mode iomode)
{	this->soap = soap_new();
	this->soap_own = true;
	MessengerServiceSoapBindingProxy_init(iomode, iomode);
	soap_endpoint = soap_endpoint_url;
}

MessengerServiceSoapBindingProxy::MessengerServiceSoapBindingProxy(soap_mode imode, soap_mode omode)
{	this->soap = soap_new();
	this->soap_own = true;
	MessengerServiceSoapBindingProxy_init(imode, omode);
}

MessengerServiceSoapBindingProxy::~MessengerServiceSoapBindingProxy()
{	if (this->soap_own)
		soap_free(this->soap);
}

void MessengerServiceSoapBindingProxy::MessengerServiceSoapBindingProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this->soap, imode);
	soap_omode(this->soap, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] = {
        { "SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope", "http://schemas.xmlsoap.org/soap/envelope/", NULL },
        { "SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://schemas.xmlsoap.org/soap/encoding/", NULL },
        { "xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL },
        { "xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL },
        { "ns1", "http://service/", NULL, NULL },
        { NULL, NULL, NULL, NULL}
    };
	soap_set_namespaces(this->soap, namespaces);
}

MessengerServiceSoapBindingProxy *MessengerServiceSoapBindingProxy::copy()
{	MessengerServiceSoapBindingProxy *dup = SOAP_NEW_UNMANAGED(MessengerServiceSoapBindingProxy);
	if (dup)
	{	soap_done(dup->soap);
		soap_copy_context(dup->soap, this->soap);
	}
	return dup;
}

MessengerServiceSoapBindingProxy& MessengerServiceSoapBindingProxy::operator=(const MessengerServiceSoapBindingProxy& rhs)
{	if (this->soap != rhs.soap)
	{	if (this->soap_own)
			soap_free(this->soap);
		this->soap = rhs.soap;
		this->soap_own = false;
		this->soap_endpoint = rhs.soap_endpoint;
	}
	return *this;
}

void MessengerServiceSoapBindingProxy::destroy()
{	soap_destroy(this->soap);
	soap_end(this->soap);
}

void MessengerServiceSoapBindingProxy::reset()
{	this->destroy();
	soap_done(this->soap);
	soap_initialize(this->soap);
	MessengerServiceSoapBindingProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

void MessengerServiceSoapBindingProxy::soap_noheader()
{	this->soap->header = NULL;
}

::SOAP_ENV__Header *MessengerServiceSoapBindingProxy::soap_header()
{	return this->soap->header;
}

::SOAP_ENV__Fault *MessengerServiceSoapBindingProxy::soap_fault()
{	return this->soap->fault;
}

const char *MessengerServiceSoapBindingProxy::soap_fault_subcode()
{	return ::soap_fault_subcode(this->soap);
}

const char *MessengerServiceSoapBindingProxy::soap_fault_string()
{	return ::soap_fault_string(this->soap);
}

const char *MessengerServiceSoapBindingProxy::soap_fault_detail()
{	return ::soap_fault_detail(this->soap);
}

int MessengerServiceSoapBindingProxy::soap_close_socket()
{	return ::soap_closesock(this->soap);
}

int MessengerServiceSoapBindingProxy::soap_force_close_socket()
{	return ::soap_force_closesock(this->soap);
}

void MessengerServiceSoapBindingProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this->soap, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void MessengerServiceSoapBindingProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this->soap, os);
}
#endif

char *MessengerServiceSoapBindingProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this->soap, buf, len);
}
#endif

int MessengerServiceSoapBindingProxy::process(const char *soap_endpoint_url, const char *soap_action, ns1__process *ns1__process_, ns1__processResponse &ns1__processResponse_)
{
	struct __ns1__process soap_tmp___ns1__process;
	if (soap_endpoint_url != NULL)
		soap_endpoint = soap_endpoint_url;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://services.stdpr.ru:8092/duplo/services/duplo2";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp___ns1__process.ns1__process_ = ns1__process_;
	soap_begin(soap);
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	soap_serialize___ns1__process(soap, &soap_tmp___ns1__process);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__process(soap, &soap_tmp___ns1__process, "-ns1:process", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__process(soap, &soap_tmp___ns1__process, "-ns1:process", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<ns1__processResponse*>(&ns1__processResponse_)) // NULL ref?
		return soap_closesock(soap);
	ns1__processResponse_.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__processResponse_.soap_get(soap, "ns1:processResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int MessengerServiceSoapBindingProxy::processGetInfo(const char *soap_endpoint_url, const char *soap_action, ns1__processGetInfo *ns1__processGetInfo_, ns1__processGetInfoResponse &ns1__processGetInfoResponse_)
{
	struct __ns1__processGetInfo soap_tmp___ns1__processGetInfo;
	if (soap_endpoint_url != NULL)
		soap_endpoint = soap_endpoint_url;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://services.stdpr.ru:8092/duplo/services/duplo2";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp___ns1__processGetInfo.ns1__processGetInfo_ = ns1__processGetInfo_;
	soap_begin(soap);
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	soap_serialize___ns1__processGetInfo(soap, &soap_tmp___ns1__processGetInfo);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__processGetInfo(soap, &soap_tmp___ns1__processGetInfo, "-ns1:processGetInfo", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__processGetInfo(soap, &soap_tmp___ns1__processGetInfo, "-ns1:processGetInfo", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<ns1__processGetInfoResponse*>(&ns1__processGetInfoResponse_)) // NULL ref?
		return soap_closesock(soap);
	ns1__processGetInfoResponse_.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__processGetInfoResponse_.soap_get(soap, "ns1:processGetInfoResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int MessengerServiceSoapBindingProxy::getVersion(const char *soap_endpoint_url, const char *soap_action, ns1__getVersion *ns1__getVersion_, ns1__getVersionResponse &ns1__getVersionResponse_)
{
	struct __ns1__getVersion soap_tmp___ns1__getVersion;
	if (soap_endpoint_url != NULL)
		soap_endpoint = soap_endpoint_url;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://services.stdpr.ru:8092/duplo/services/duplo2";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp___ns1__getVersion.ns1__getVersion_ = ns1__getVersion_;
	soap_begin(soap);
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	soap_serialize___ns1__getVersion(soap, &soap_tmp___ns1__getVersion);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__getVersion(soap, &soap_tmp___ns1__getVersion, "-ns1:getVersion", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__getVersion(soap, &soap_tmp___ns1__getVersion, "-ns1:getVersion", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!static_cast<ns1__getVersionResponse*>(&ns1__getVersionResponse_)) // NULL ref?
		return soap_closesock(soap);
	ns1__getVersionResponse_.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__getVersionResponse_.soap_get(soap, "ns1:getVersionResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}
/* End of client proxy code */