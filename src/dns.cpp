#include "dns.h"

#include <ldns/ldns.h>

#include <iostream>

Dns::Dns() {
  ldns_status status = ldns_resolver_new_frm_file(&resolver, NULL);

  if (status != LDNS_STATUS_OK) {
    std::cerr << "Unable to create DNS resolver" << std::endl;
    exit(1);
  }
}

bool Dns::is_domain_valid(const string name) {
  
  ldns_rdf *domain = ldns_dname_new_frm_str(name.c_str());

  if (!domain) {
    std::cerr << "Unable to create domain" << std::endl;
    return false;
  }

  ldns_pkt *packet = ldns_resolver_search(this->resolver, domain, LDNS_RR_TYPE_MX,
                                LDNS_RR_CLASS_IN, LDNS_RD);
  ldns_rdf_deep_free(domain);

  if (!packet) {
    std::cerr << "Unable to search for mx record" << std::endl;
    return false;
  }
  ldns_rr_list *mx =
      ldns_pkt_rr_list_by_type(packet, LDNS_RR_TYPE_MX, LDNS_SECTION_ANSWER);
  if (!mx) {
    std::cout << "Domain not found" << std::endl;
    ldns_pkt_free(packet);
    return false;
  } else {
    std::cout << "Domain found" << std::endl;
    ldns_rr_list_deep_free(mx);
    ldns_pkt_free(packet);
    return true;
  }
}
