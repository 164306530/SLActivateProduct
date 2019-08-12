HCERTSTORE hSysStore;
hSysStore = CertOpenStore(
   CERT_STORE_PROV_SYSTEM,   // the store provider type
   0,                        // the encoding type is not needed
   NULL,                     // use the default HCRYPTPROV
   CERT_SYSTEM_STORE_CURRENT_USER,
                             // set the store location in a 
                             // registry location
   L"My"    // the store name as a Unicode string
   );

// If call was successful, close hSystStore; otherwise, 
// call print an error message.
if(hSysStore)
{
    if (!(CertCloseStore(hSysStore, 0)))
    {
        printf("Error closing system store.");
    }
}
else
   printf("Error opening system store.");


// Substitute other common system store names
// for "My" 
// including "root", "trust", or "CA".
