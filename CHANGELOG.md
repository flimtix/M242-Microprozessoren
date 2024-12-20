# Changelog

<a name="1.2.0"></a>
## 1.2.0 (2024-12-20)

### Added

- ✨ : StateEvent for controlling the state [[eb87567](https://github.com/flimtix/M242-Microprozessoren/commit/eb8756746f2e8301d531d11b5b7be840953d5841)]
- ✨ : Timer events [[4eb8b4d](https://github.com/flimtix/M242-Microprozessoren/commit/4eb8b4d45031b206dfd61ef5a657e12f70eabf1f)]
- ✨ : Stopwatch events [[27ad8f0](https://github.com/flimtix/M242-Microprozessoren/commit/27ad8f01e6e5bb8ad2579d2b25f8fda3cd41405b)]
- ✨ : Add Buzzer driver [[caf51cb](https://github.com/flimtix/M242-Microprozessoren/commit/caf51cba15e996d9773d3739ec151c224d847fd0)]
- ✨ : Added display driver [[f9d28df](https://github.com/flimtix/M242-Microprozessoren/commit/f9d28df6d44ab788d7bd73f2b160ec5b3426d9a2)]
- ✨ Added Seg_Driver for controlling the display [[f86a90d](https://github.com/flimtix/M242-Microprozessoren/commit/f86a90da5e8a7ccf7455e889d6f9d419861ebb97)]
- 🎉 : Init STM-Cube project [[1982469](https://github.com/flimtix/M242-Microprozessoren/commit/1982469af320903df07d7097f7ac7e0ce0ffede6)]

### Changed

- 🚚 : Renamed methods [[f6ca829](https://github.com/flimtix/M242-Microprozessoren/commit/f6ca82977e0de71750490b7e1d6befb45531d923)]
- ⚡ : Use Led_Toggle instead of set [[e7afb0b](https://github.com/flimtix/M242-Microprozessoren/commit/e7afb0ba8315d17715dea1c8508e189b314db52f)]
- ⚡ : Buzzer in its own task [[9164d65](https://github.com/flimtix/M242-Microprozessoren/commit/9164d652354567934f1af99eba9058955e09abd5)]
- 🏗️ : Taster interrupt fires on low/high &amp; array for storage [[4b71dcf](https://github.com/flimtix/M242-Microprozessoren/commit/4b71dcf17a5e1fba930b4f51eb051c8f673fae3b)]
- 🎨 : place the number of call outside of the buzzer [[ca0e2f7](https://github.com/flimtix/M242-Microprozessoren/commit/ca0e2f797fcbff51bcf69a7e4f3f8529addfe50d)]
- ⬆️ : STM now allows external tasks [[ff8f881](https://github.com/flimtix/M242-Microprozessoren/commit/ff8f881c9a03bd83b24464d1ecba08fd9dcf71f8)]
- 🏗️ : Static Task &amp; display is low priority [[0072eb1](https://github.com/flimtix/M242-Microprozessoren/commit/0072eb11d3ef54cb40a8505f3644f800a802cb1e)]
- 🏗️ : Use static semaphores [[3947301](https://github.com/flimtix/M242-Microprozessoren/commit/394730182689dfa608db164b26471d2b84408efd)]
- 🏗️ : Taster driver with interrupts and callbacks [[77ef379](https://github.com/flimtix/M242-Microprozessoren/commit/77ef37959e215761981e13d9faac63f28e91b7ec)]
- 🔧 : STM Update things [[a202f5c](https://github.com/flimtix/M242-Microprozessoren/commit/a202f5c7e20411bea32952bf268139ed35376250)]
- 🚨 : Can compile [[54c842b](https://github.com/flimtix/M242-Microprozessoren/commit/54c842ba4eb246948e1b8bc7989527868a0db329)]
- 🔧 : Prettier config [[850b329](https://github.com/flimtix/M242-Microprozessoren/commit/850b329bf64b34309e6aea9eacdadb9f762d0ff6)]
- 🔧 : Add gitmoji config [[8e1e92a](https://github.com/flimtix/M242-Microprozessoren/commit/8e1e92a38e7587372bd7c4ef8cd1438e9674a474)]

### Removed

- ➖ : Removed semaphore for the display [[e0a9708](https://github.com/flimtix/M242-Microprozessoren/commit/e0a9708c63aaa407962cecde6b510fa2fee105a1)]

### Fixed

- 🐛 : Reset timer if paused [[ab5c622](https://github.com/flimtix/M242-Microprozessoren/commit/ab5c622be43f89270b3b98e65899b34096eaf874)]
- 🐛 : Bug fixes &amp; cleanup [[cdc5804](https://github.com/flimtix/M242-Microprozessoren/commit/cdc5804ae7b35ae14c92b4935de5a895042a4c78)]
- 🚑 : Taster callbacks are triggered in a task [[db1efb0](https://github.com/flimtix/M242-Microprozessoren/commit/db1efb043d44ba4f67d55933863979e192e92355)]
- 🐛 : Buzzer semaphore as extern [[1f796f3](https://github.com/flimtix/M242-Microprozessoren/commit/1f796f3962ef9ba9665ab18ba3a9b3f4b443afee)]
- 🐛 : Only allow changes to timer when configuring [[3ca5b1c](https://github.com/flimtix/M242-Microprozessoren/commit/3ca5b1cf5d60111e29556475614f7295cf0da9b5)]
- 🐛 : Reset the intermediate time on stop and start [[a5011f1](https://github.com/flimtix/M242-Microprozessoren/commit/a5011f165b1e909f32b3f22f61d4c637f757143e)]
- 🐛 : LED_Treiber semaphore as extern [[3e7aa7e](https://github.com/flimtix/M242-Microprozessoren/commit/3e7aa7e918bb7ca5ae3be71c4063f5bd6b70e227)]
- 🐛 : display semaphore as extern &amp; use unsigned int [[e0cbbed](https://github.com/flimtix/M242-Microprozessoren/commit/e0cbbede02aadda79aa94f1c8c7407218002f9c7)]
- 🐛 : I dont know why?!? [[2d74f0f](https://github.com/flimtix/M242-Microprozessoren/commit/2d74f0f5cd5efc7c79b49121b586ffcdafe02104)]
- 🐛 : Use the correct taster enum [[ad81fea](https://github.com/flimtix/M242-Microprozessoren/commit/ad81fea8dace0b76b69a91d09445e0b8960c9086)]
- 🐛 : Start the real Taster_Treiber [[425ae04](https://github.com/flimtix/M242-Microprozessoren/commit/425ae046b690d527adbbb04a9f1f76848db5bfc0)]
- 💚 : Add on to gitmoji [[f59490a](https://github.com/flimtix/M242-Microprozessoren/commit/f59490a97addd1c218e578bb95f0ce6e55f1a63a)]
- 💚 : Run gitmoji on commit [[3c9d564](https://github.com/flimtix/M242-Microprozessoren/commit/3c9d5641ff73c9b17c803e83fb7a6b21ebfaa633)]

### Miscellaneous

- 📝 : Update URL in README.md [[54e5dd2](https://github.com/flimtix/M242-Microprozessoren/commit/54e5dd22bcd189b52987ab04fa94b48665407b70)]
-  Merge branch &#x27;main&#x27; of https://github.com/21r8390/M242-Microprozessoren [[99a77a5](https://github.com/flimtix/M242-Microprozessoren/commit/99a77a5bd0afe5970d01fae9cb59df08ed4e3c4c)]
- 📝 : Added project requirements [[4294d35](https://github.com/flimtix/M242-Microprozessoren/commit/4294d35bc42055763aaeff578bfe682f892d1f94)]
- 📝 : Added Fazit [[f8d7818](https://github.com/flimtix/M242-Microprozessoren/commit/f8d781868d17f2b262c72b92792d4a422b9e5db2)]
- 📝 : Update changelog [[2c9b2da](https://github.com/flimtix/M242-Microprozessoren/commit/2c9b2da7c7984c160a76319c1c2e74a88df491ac)]
- 📝 : Update changelog [[43233f5](https://github.com/flimtix/M242-Microprozessoren/commit/43233f5689c407b753f00daeae9ede95c1e8a35b)]
- 📝 : Component diagram &amp; Readme with UMLs [[ebba8f0](https://github.com/flimtix/M242-Microprozessoren/commit/ebba8f0eed84137973495e4eb8117cf70ed77884)]
- 📝 : Added class diagram [[581a95b](https://github.com/flimtix/M242-Microprozessoren/commit/581a95bfa7d02e4e697f2e6eb28479fff0e65e41)]
- 📝 : Update State-Event-Diagramm [[9ec98ef](https://github.com/flimtix/M242-Microprozessoren/commit/9ec98ef3215d93affb8b47c179bd16a723e56782)]
- 📝 : Update changelog [[fe00af0](https://github.com/flimtix/M242-Microprozessoren/commit/fe00af009def4a54c3a82293ce0f16f088068632)]
- 📝 : Added State-Event_Diagramm [[34af5bf](https://github.com/flimtix/M242-Microprozessoren/commit/34af5bfce4cc5ab98ebd509ee25e89ff4c24fa31)]
- 🧑‍💻 : Improved code and small bugs [[de66fdc](https://github.com/flimtix/M242-Microprozessoren/commit/de66fdce7744044265f1d37e0650129da4762177)]
- 🩹 : Buzzer now works with the current ticks and allows multiple calls [[39d6b9d](https://github.com/flimtix/M242-Microprozessoren/commit/39d6b9d022b444aa94ca55b4baa511a2f0841f1a)]
- 📝 : Update changelog [[ffeb75c](https://github.com/flimtix/M242-Microprozessoren/commit/ffeb75c573458940abadbc3442d30980d81d0c60)]
-  Merge branch &#x27;main&#x27; of https://github.com/21r8390/M242-Microprozessoren [[55740e7](https://github.com/flimtix/M242-Microprozessoren/commit/55740e7662b083b7506e2709255ed95787878a54)]
- ⚰️ : Aufgaben is not needed [[55485c5](https://github.com/flimtix/M242-Microprozessoren/commit/55485c56a127c1d4a3c0f7ac4af1e5f2edd2ac7e)]
-  Merge branch &#x27;main&#x27; of https://github.com/21r8390/M242-Microprozessoren [[795bb4e](https://github.com/flimtix/M242-Microprozessoren/commit/795bb4ec40382ecbd61a99c991d9b1784fe0e5ca)]
- 📝 : Update changelog [[a3e0c98](https://github.com/flimtix/M242-Microprozessoren/commit/a3e0c98911d6c99ae5e4790bfc18d850f3914970)]
- 🍻 : Reading taster does not need a semaphore [[37dfe62](https://github.com/flimtix/M242-Microprozessoren/commit/37dfe620ecc956c1d9c5e332fcd4f183d8bbd3e5)]
- 💡 : Added more comments to the display driver [[7b792ea](https://github.com/flimtix/M242-Microprozessoren/commit/7b792ea8181a7640c9f8564d920cf292e3d4abb4)]
- 📝 : Update changelog [[e809605](https://github.com/flimtix/M242-Microprozessoren/commit/e8096051d913c425b48090e7316e89abf9aac962)]
- 🧵 : LED driver extended by semaphore [[a5e614c](https://github.com/flimtix/M242-Microprozessoren/commit/a5e614ccce7603f7250cdcaec396cd93f4cdde74)]
- 🍻 : Tests for Seg_Driver [[997cf7d](https://github.com/flimtix/M242-Microprozessoren/commit/997cf7d31c078f2d5efba3344c9e3043cbb9079e)]
-  LED mit richtigem Enum [[9ee0e87](https://github.com/flimtix/M242-Microprozessoren/commit/9ee0e872fe7db5917821cd65bf5b5b70563cc17a)]
-  LED driver now uses an enum [[8bcad36](https://github.com/flimtix/M242-Microprozessoren/commit/8bcad366ed72aa73e8bf8cd8b37c42f410aac1bf)]
- 📝 : Added documentation and snake [[b46130f](https://github.com/flimtix/M242-Microprozessoren/commit/b46130faac3af4eaa6aa14501557fb6263c09ef0)]
- 📝 : Update changelog [[130f6e9](https://github.com/flimtix/M242-Microprozessoren/commit/130f6e9c0dd55944afa5a7ba7d0e1d1a7f0990c2)]
- 📝 : Update changelog [[5847b41](https://github.com/flimtix/M242-Microprozessoren/commit/5847b41e8c21254be38fb0cbb8ee54532234d082)]
- 📝 : Update changelog [[82937ef](https://github.com/flimtix/M242-Microprozessoren/commit/82937efc46407e4c0ea99c65671dea053b153ed0)]
-  Merge branch &#x27;main&#x27; of https://github.com/21r8390/M242-Microprozessoren [[06968cf](https://github.com/flimtix/M242-Microprozessoren/commit/06968cf8a78de5171aecb88019951221b90c1973)]
-  .gitignore is now working [[5d06698](https://github.com/flimtix/M242-Microprozessoren/commit/5d066985fda964d87bba988bac777f8c104a7fe0)]
- 💩 : .metadata changes [[937fcb2](https://github.com/flimtix/M242-Microprozessoren/commit/937fcb2c9e0467378f23954e23a6f65d0484c0be)]
- 📝 : Update changelog [[8831ca4](https://github.com/flimtix/M242-Microprozessoren/commit/8831ca4e2b3c3b47f92cc3875a64f12c61edfb60)]
- 📝 : Update changelog [[46f9438](https://github.com/flimtix/M242-Microprozessoren/commit/46f9438478c30e1aea8b592dea05025f865ab73c)]
-  Update gitmoji.yml [[2b93729](https://github.com/flimtix/M242-Microprozessoren/commit/2b937296015086052dabc422ea7a01226a56ea9a)]
- 📝 : Update changelog [[9f15060](https://github.com/flimtix/M242-Microprozessoren/commit/9f15060c49b2161ce51fbafbafbafbfd5b6d3829)]
- 📝 : Update changelog [[e8e6ff6](https://github.com/flimtix/M242-Microprozessoren/commit/e8e6ff66974b6ab621edc31ea607dd95961f7776)]
- 🧱 : Update things [[d0d9cf6](https://github.com/flimtix/M242-Microprozessoren/commit/d0d9cf6f107d4b795cd5c41fa8249b0b81b2e82a)]
- 🙈 : Added Debug &amp; .metadata to .gitignore [[e5aa5bd](https://github.com/flimtix/M242-Microprozessoren/commit/e5aa5bd96917d4abb8ffb419a4fb5b9b28b94487)]
- 👔 : Add Taster_Treiber [[f3e3037](https://github.com/flimtix/M242-Microprozessoren/commit/f3e30379221c3d2658f268e1ff8a5dbe4cb7cb55)]
- 👔 : Add LED_Treiber [[9d27a68](https://github.com/flimtix/M242-Microprozessoren/commit/9d27a682277581f9bbfbfaa229bd390dff759f6d)]
- 🌱 : Init c &amp; h Template [[449f5aa](https://github.com/flimtix/M242-Microprozessoren/commit/449f5aa267b042ce16d5298a90d49343c6027e73)]
-  👷: gitmoji release notes [[261c19a](https://github.com/flimtix/M242-Microprozessoren/commit/261c19a6305afd729f688af8cd7d0782d59bee41)]
-  Initial commit [[5a12a34](https://github.com/flimtix/M242-Microprozessoren/commit/5a12a34d7b0085f090f5ecc1fd2bf1d7cd6b98e1)]


