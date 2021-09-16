dfu-programmer atxmega128a4u erase && \
dfu-programmer atxmega128a4u flash-eeprom Chameleon-RevG.eep --force && \
dfu-programmer atxmega128a4u flash Chameleon-RevG.hex && \
dfu-programmer atxmega128a4u launch
