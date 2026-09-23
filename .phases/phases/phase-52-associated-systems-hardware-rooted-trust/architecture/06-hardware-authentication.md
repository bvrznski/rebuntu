# Hardware-Rooted Assurance

Hardware authenticators are optional assurance providers, not the architecture itself.

FIDO2/WebAuthn/U2F, smartcards/PIV, TPM-backed keys or other hardware may be used where their actual supported primitives fit the protocol.

Never assume a FIDO/U2F private key can be exported, cloned or used as an arbitrary Diffie-Hellman key.

Hardware presence may authorize issuance/acceptance/change/revocation of an association without becoming the transport/session key.
