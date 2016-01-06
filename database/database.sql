CREATE TABLE public.connections
(
  "DateTime" timestamp,
  "UnitId" bigint,
  "Port" character varying,
  "Value" integer
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.connections
  OWNER TO postgres;
CREATE TABLE public.events
(
  "DateTime" timestamp,
  "UnitId" bigint,
  "Port" character varying,
  "Value" integer
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.events
  OWNER TO postgres;
CREATE TABLE public.monitoring
(
  "UnitId" bigint,
  "BeginTime" timestamp,
  "EndTime" timestamp,
  "Type" character varying,
  "Min" double precision,
  "Max" double precision,
  "Sum" double precision
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.monitoring
  OWNER TO postgres;
CREATE TABLE public.positions
(
  "DateTime" timestamp,
  "UnitId" bigint,
  "Rdx" double precision,
  "Rdy" double precision,
  "Speed" bigint,
  "Course" double precision,
  "NumSatellites" integer,
  "HDOP" integer,
  "Quality" character varying
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.positions
  OWNER TO postgres;