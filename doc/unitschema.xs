<?xml version"1.0"?>
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">

<xs:element name="unit">
  <xs:complexType>
    <xs:all>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="id">
        <xs:simpleType>
          <xs:restriction base="xs:string">
            <xs:minLength value="1"/>
            <xs:maxLength value="8"/>
          </xs:restriction>
        </xs:simpleType>
      </xs:element>
      <xs:element name="desc" type="xs:string"/>
      <xs:element name="cost" type="xs:unsignedShort"/>
      <xs:element name="upkeep">
        <xs:complexType>
          <xs:attribute name="gold" type="xs:unsignedByte" use="required"/>
          <xs:attribute name="food" type="xs:unsignedByte" use="required"/>
          <xs:attribute name="mana" type="xs:unsignedByte" use="required"/>
        </xs:complexType>
      </xs:element>
      <xs:element name="units">
        <xs:simpleType>
          <xs:restriction base="xs:integer">
            <xs:minInclusive value="1"/>
            <xs:maxInclusive value="8"/>
          </xs:restriction>
        </xs:simpleType>
      </xs:element>
      <xs:element name="health" type="xs:unsignedByte"/>
      <xs:element name="attack" type="xs:unsignedByte"/>
      <xs:element name="tohitbonus" type="xs:unsignedByte" minOccurs="0"/>
      <xs:element name="ranged" minOccurs="0">
        <xs:complexType>
          <xs:simpleContent>
            <xs:extension base="xs:unsignedByte">
              <xs:attribute name="ammo" type="xs:unsignedByte" use="required"/>
              <xs:attribute name="type" use="required">
                <xs:simpleType>
                  <xs:restriction base="xs:string">
                    <xs:enumeration value="MISSILE"/>
                    <xs:enumeration value="STONE"/>
                    <xs:enumeration value="MAGIC"/>
                  </xs:restriction>
                </xs:simpleType>
              </xs:attribute>
            </xs:extension>
          </xs:simpleContent>
        </xs:complexType>
      </xs:element>
      <xs:element name="defense" type="xs:unsignedByte"/>
      <xs:element name="resistance" type="xs:unsignedByte"/>
      <xs:element name="movement">
        <xs:complexType>
          <xs:simpleContent>
            <xs:extension base="xs:unsignedByte">
              <xs:attribute name="type" use="required">
                <xs:simpleType>
                  <xs:restriction base="xs:string">
                    <xs:enumeration value="WALK"/>
                    <xs:enumeration value="WALKSWIM"/>
                    <xs:enumeration value="SWIM"/>
                    <xs:enumeration value="FLY"/>
                  </xs:restriction>
                </xs:simpleType>
              </xs:attribute>
            </xs:extension>
          </xs:simpleContent>
        </xs:complexType>
      </xs:element>
      <xs:element name="type">
        <xs:simpleType>
          <xs:restriction base="xs:string">
            <xs:enumeration value="MUNDANE"/>
            <xs:enumeration value="ARCANE"/>
            <xs:enumeration value="SORCERY"/>
            <xs:enumeration value="CHAOS"/>
            <xs:enumeration value="LIFE"/>
            <xs:enumeration value="DEATH"/>
            <xs:enumeration value="NATURE"/>
          </xs:restriction>
        </xs:simpleType>
      </xs:element>
      <xs:element name="abilities" minOccurs="0">
        <xs:complexType>
          <xs:attribute name="armor_piercing" type="xs:boolean"/>
          <xs:attribute name="cause_fear" type="xs:boolean"/>
          <xs:attribute name="caster" type="xs:unsignedByte"/>
          <xs:attribute name="cold_immune" type="xs:boolean"/>
          <xs:attribute name="construction" type="xs:boolean"/>
          <xs:attribute name="create_outpost" type="xs:boolean"/>
          <xs:attribute name="create_undead" type="xs:boolean"/>
          <xs:attribute name="death_gaze" type="xs:unsignedByte"/>
          <xs:attribute name="death_immunity" type="xs:boolean"/>
          <xs:attribute name="dispel_evil" type="xs:boolean"/>
          <xs:attribute name="doom_bolt_spell" type="xs:boolean"/>
          <xs:attribute name="doom_gaze" type="xs:unsignedByte"/>
          <xs:attribute name="fireball_spell" type="xs:boolean"/>
          <xs:attribute name="fire_breath" type="xs:unsignedByte"/>
          <xs:attribute name="fire_immunity" type="xs:boolean"/>
          <xs:attribute name="first_strike" type="xs:boolean"/>
          <xs:attribute name="forester" type="xs:boolean"/>
          <xs:attribute name="healer" type="xs:boolean"/>
          <xs:attribute name="healing_spell" type="xs:boolean"/>
          <xs:attribute name="holy_bonus" type="xs:unsignedByte"/>
          <xs:attribute name="illusion" type="xs:boolean"/>
          <xs:attribute name="illusion_spell" type="xs:boolean"/>
          <xs:attribute name="immolation" type="xs:boolean"/>
          <xs:attribute name="invisibility" type="xs:boolean"/>
          <xs:attribute name="large_shield" type="xs:boolean"/>
          <xs:attribute name="life_steal" type="xs:unsignedByte"/>
          <xs:attribute name="lightning_breath" type="xs:unsignedByte"/>
          <xs:attribute name="long_range" type="xs:boolean"/>
          <xs:attribute name="lucky" type="xs:boolean"/>
          <xs:attribute name="magic_immunity" type="xs:boolean"/>
          <xs:attribute name="meld" type="xs:boolean"/>
          <xs:attribute name="merging" type="xs:boolean"/>
          <xs:attribute name="missile_immunity" type="xs:boolean"/>
          <xs:attribute name="mountaineer" type="xs:boolean"/>
          <xs:attribute name="negate_first_strike" type="xs:boolean"/>
          <xs:attribute name="noncorporeal" type="xs:boolean"/>
          <xs:attribute name="pathfinding" type="xs:boolean"/>
          <xs:attribute name="plane_shift" type="xs:boolean"/>
          <xs:attribute name="poison_immunity" type="xs:boolean"/>
          <xs:attribute name="poison_touch" type="xs:unsignedByte"/>
          <xs:attribute name="purify" type="xs:boolean"/>
          <xs:attribute name="regeneration" type="xs:boolean"/>
          <xs:attribute name="resistance_to_all" type="xs:unsignedByte"/>
          <xs:attribute name="scouting" type="xs:unsignedByte"/>
          <xs:attribute name="stoning_gaze" type="xs:unsignedByte"/>
          <xs:attribute name="stoning_immunity" type="xs:boolean"/>
          <xs:attribute name="stoning_touch" type="xs:unsignedByte"/>
          <xs:attribute name="summon_demons" type="xs:boolean"/>
          <xs:attribute name="teleporting" type="xs:boolean"/>
          <xs:attribute name="thrown" type="xs:unsignedByte"/>
          <xs:attribute name="wall_crusher" type="xs:boolean"/>
          <xs:attribute name="weapon_immunity" type="xs:boolean"/>
          <xs:attribute name="web_spell" type="xs:boolean"/>
          <xs:attribute name="wind_walking" type="xs:boolean"/>
        </xs:complexType>
      </xs:element>
    </xs:all>
  </xs:complexType>
</xs:element>

</xs:schema>
