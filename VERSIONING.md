<!--
Copyright (c) 2020-2024 Key4hep-Project.

This file is part of Key4hep.
See https://key4hep.github.io/key4hep-doc/ for further info.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
-->
This project uses a lightweight Semantic Versioning scheme with optional status suffixes. Tags are used to mark reproducible states of the analysis.

# Format

vMAJOR.MINOR.PATCH[-status]

- __MAJOR__ → Big changes to the workflow (e.g. restructuring to Gaudi, switching frameworks, redoing data model).
- __MINOR__ → New or improved functionality (e.g. adding new selection criteria, new plots, new automation scripts).
- __PATCH__ → Small fixes or tweaks (e.g. bug fixes, small config updates).
	- -status (optional) → Development state:
	- -stable → End-to-end analysis chain runs successfully.
	- -wip → Work in progress, partial functionality.
	- -broken → Known non-working but tagged for historical purposes.

# Tagging Guidelines
- __Tag stable milestones__ that you may need to reproduce (e.g. for a presentation, note, or internal report).
- __Tag before large restructuring__ to have an easy rollback point.
- __Tag at least once per major analysis stage__ (dataset preparation, selection implemented, first plots, systematics, final results).
- Do __not__ tag every commit — tags are for checkpoints, not history of all changes.

# Examples
- v1.0.0-stable → First full working version of the chain.
- v1.1.0-wip → Started adding new selection, not fully validated.
- v1.1.1-stable → Fixed bug, working again.
- v2.0.0-stable → Major restructuring: migrated to Gaudi + edm4hep.
